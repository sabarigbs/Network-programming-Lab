BEGIN{
	sentPackets = 0;
}
{
	if($1 == '+')
		sentPackets++;
}
END{
	printf("%d sent packets ",sentPackets);
}