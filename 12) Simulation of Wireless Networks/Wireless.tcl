set x 500
set y 500
set n 2
set ns_ [new Simulator]
set topo [new Topography]
$topo load flatgrid $x $y
set tracefd [open wireless.tr w]
$ns_ trace-all $tracefd
$ns_ use-newtrace
set namtrace-all-wireless $namtracefd $x $y
set god_ [create-god $n]

$ns_ node-config -adhocRouting AODV \
		--llType LL \
		-macType Mac/802_11 \
		-ifqType Queue/DropTail/PriQueue \
		-ifqLen 50 \
		-antType Antenna/OmniAntenna \
		-propType Propagation/TwoRayGround \
		-phyType Phy/WirelessPhy \
		-channelType Channel/WirelessChannel \
		-topoInstance $topo \
		-agentTrace ON \
		-routerTrace ON \
		-macTrace OFF \

for {set i 0} { $i < $n } {incr i} {
set node_($i)[$ns_ node]
}
 
$node_(0) set X_ 50.0
$node_(0) set Y_ 50.0
$node_(0) set Z_ 0.0

$node_(1) set X_ 200.0
$node_(1) set Y_ 150.0
$node_(1) set Z_ 0.0

for {set i 0} { $i < $n } {incr i} {
$ns_ initial_node_pos $node_($i) 30
}

set tcp0 [new Agent/UDP]
$ns_ attach-agent $node_(0) $tcp0

set sink0 [new Agent/Null]
$ns_ attach-agent $node_(1) $sink0

set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.025
$cbr0 attach-agent $tcp0

$ns_ at 1 "$cbr0 start"
$ns_ at 5 "$node_(0) setdest 100 200 10"
$ns_ at 10 "$cbr0 stop" 

$ns_ at 100.0 "$ns halt"
$ns_ run
