BEGIN {
recvdSize = 0
startTime = 400
stopTime = 0

seqno = -1;
droppedPackets = 0;
receivedPackets = 0;
count = 0;
}
{
event = $1
time = $2
node_id = $3
pkt_size = $8
level = $4
# Store start time


if (level == "AGT" && event == "s" && seqno < $6) {
seqno = $6;
if (time < startTime) {
startTime = time
}
}
# Update total received packets' size and store packets arrival time
if (level == "AGT" && event == "r" ) {
receivedPackets++;
if (time > stopTime) {
stopTime = time
}


recvdSize += pkt_size
}


if ($1 == "D" && $7 == "tcp" && $8 > 4){
droppedPackets++;
}
}

END {
printf("Average Throughput[kbps] = %.2f\t\t\nStartTime=%.2f\t\nStopTime= %.2f\n",(recvdSize/(stopTime-startTime))*(8/1000),startTime,stopTime);

printf("Packet Delivery Ratio = %.2f \n", receivedPackets/(seqno+1)*100);
}
