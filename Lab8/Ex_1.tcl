set ns_ [new Simulator]
set tracefd [open simple.tr w]
$ns_ trace-all $tracefd
set namtrace [open out.nam w]
$ns_ namtrace-all-wireless $namtrace 500 500
set topo [new Topography]
$topo load_flatgrid 500 500
create-god 5
$ns_ node-config -adhocRouting DSDV \
-llType LL \
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
-movementTrace OFF
for {set i 0} {$i < 7} {incr i} {
set node_($i) [$ns_ node]
$node_($i) random-motion 0 ;
}
$node_(0) set X_ 0.0
$node_(0) set Y_ 0.0
$node_(0) set Z_ 0.0
$node_(1) set X_ 0.0
$node_(1) set Y_ 0.0
$node_(1) set Z_ 0.0
$node_(2) set X_ 0.0
$node_(2) set Y_ 0.0
$node_(2) set Z_ 0.0
$node_(3) set X_ 0.0
$node_(3) set Y_ 0.0
$node_(3) set Z_ 0.0
$node_(4) set X_ 0.0
$node_(4) set Y_ 0.0
$node_(4) set Z_ 0.0
$node_(5) set X_ 0.0
$node_(5) set Y_ 0.0
$node_(5) set Z_ 0.0
$ns_ at 50.0 "$node_(0) setdest 100.0 100.0 15.0"
$ns_ at 50.0 "$node_(1) setdest 200.0 100.0 15.0"
$ns_ at 50.0 "$node_(2) setdest 300.0 100.0 15.0"
$ns_ at 50.0 "$node_(3) setdest 150.0 200.0 15.0"
$ns_ at 50.0 "$node_(4) setdest 250.0 200.0 15.0"
$ns_ at 50.0 "$node_(5) setdest 200.0 300.0 15.0"
#$ns_ at 100.0 "$node_(1) setdest 490.0 480.0 15.0"
#$n0 radius 20
#$god set-dist 0 1 2
set tcp [new Agent/TCP]
$tcp set class_ 2
set sink [new Agent/TCPSink]
$ns_ attach-agent $node_(3) $tcp
$ns_ attach-agent $node_(5) $sink
$ns_ connect $tcp $sink
set ftp [new Application/FTP]
$ftp attach-agent $tcp

$ns_ at 10.0 "$ftp start"
for {set i 0} {$i < 7 } {incr i} {
$ns_ at 150.0 "$node_($i) reset";
}
$ns_ at 150.0 "stop"
$ns_ at 150.01 "puts \"NS EXITING...\" ; $ns_ halt"
proc stop {} {
global ns_ tracefd
$ns_ flush-trace
close $tracefd
exec nam out.nam &
}
puts "Starting Simulation..."
$ns_ run
