set ns [new Simulator]

set tr [open tr.tr "w"]
set out [open out.nam "w"]

$ns namtrace-all $out
$ns trace-all $tr

proc finish { } {
    global ns tr out
    $ns flush-trace
    close $tr
    close $out
    exec nam out.nam &
    exit 0
}

set n0 [$ns node]
set n1 [$ns node]

$ns duplex-link $n0 $n1 10Mb 3ms DropTail

set tcp [new Agent/TCP]
set sink [new Agent/TCPSink]

$ns attach-agent $n0 $tcp
$ns attach-agent $n1 $sink

$ns connect $tcp $sink


set ftp [new Application/FTP]
$ftp attach-agent $tcp

$ns at 0.1 "$ftp start"
$ns at 500 "$ftp stop"
$ns at 500.1 "finish"
$ns run



