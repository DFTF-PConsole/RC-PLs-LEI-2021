# Resolução do Trab 1
# Vasco Pereira 2015
# Introdução às Redes de Comunicação
# Universidade de Coimbra

if {$argc == 7} {
	set protocol [lindex $argv 0]
	set tcp_window [lindex $argv 1]
	set stream_rate [lindex $argv 2]
	set break_connection [lindex $argv 3]
	set speed [lindex $argv 4]
	set simulation_time [lindex $argv 5]
	set network_anim [lindex $argv 6]
} else {
	puts "Usage: ns $argv0 {protocol(tcp/udp)} {tcp_window(if udp put 0)} {stream_rate} {break_connection(yes/no)} {Speed Server1-R4(0=DEFAULT)} {simulation time} {nam}"
	exit 1
}


# Create the 'Simulator' object
set ns [new Simulator]

# Routing protocol
$ns rtproto DV

# Open a file for writing the nam trace data
set trace_nam [open out.nam w]
set trace_nt [open out.tr w]

$ns namtrace-all $trace_nam
$ns trace-all $trace_nt

# Add a 'finish' procedure that closes the traces and starts nam
proc finish {} {
    global ns trace_nam trace_nt network_anim
    $ns flush-trace
		if { $network_anim == "on" } {
    	exec nam out.nam &
			}
    exit 0
}

# Color Codes
$ns color 1 Red		;# set color of packets for a specified fid (flow id)
$ns color 2 Blue
$ns color 3 Green

#############################################################################

# Define the topology
set n0 [$ns node] ;# Serv 1 - Node 0
set n1 [$ns node] ;# Serv 2 - Node 1
set n2 [$ns node] ;# Rec 1 - Node 2
set n3 [$ns node] ;# Rec 2 - Node 3
set n4 [$ns node] ;# Router 4 - Node 4
set n5 [$ns node] ;# Router 5 - Node 5
set n6 [$ns node] ;# Router 6 - Node 6

#labels
$n0 label "Servidor 1"
$n1 label "Servidor 2"
$n2 label "Recetor 1"
$n3 label "Recetor 2"
$n4 label "R4"
$n5 label "R5"
$n6 label "R6"

# Paint nodes
$n0 color Red
$n1 color Red
$n2 color Blue
$n3 color Blue

#Shapes
$n0 shape hexagon
$n1 shape hexagon
$n2 shape box
$n3 shape box


#   object      from  to  bandwith	delay	queue
if {$speed == "0"} {
	$ns duplex-link $n0   $n4 50Mb	10ms	DropTail
	} else {
	$ns duplex-link $n0   $n4 $speed	10ms	DropTail
	}

$ns duplex-link $n1   $n5 100Mb		10ms	DropTail
$ns duplex-link $n4   $n5 200Mb		10ms	DropTail
$ns duplex-link $n4   $n6 1000Mb	10ms	DropTail
$ns duplex-link $n5   $n6 100Mb		10ms	DropTail
$ns duplex-link $n6   $n2 40Mb		3ms	DropTail
$ns duplex-link $n4   $n3 10Mb		10ms	DropTail

$ns duplex-link-op $n0 $n4 orient down
$ns duplex-link-op $n4 $n3 orient down
$ns duplex-link-op $n4 $n6 orient right-down
$ns duplex-link-op $n4 $n5 orient right
$ns duplex-link-op $n6 $n5 orient up
$ns duplex-link-op $n5 $n1 orient up
$ns duplex-link-op $n6 $n2 orient right

$ns duplex-link-op $n0 $n4 queuePos 0.5
$ns duplex-link-op $n1 $n5 queuePos 0.5
$ns duplex-link-op $n4 $n5 queuePos 0.5
$ns duplex-link-op $n4 $n6 queuePos 0.5
$ns duplex-link-op $n5 $n6 queuePos 0.5
$ns duplex-link-op $n6 $n2 queuePos 0.5
$ns duplex-link-op $n4 $n3 queuePos 0.5

$ns duplex-link-op $n0 $n4 label "v=50Mb"
$ns duplex-link-op $n1 $n5 label "v=0.1Gb"
$ns duplex-link-op $n4 $n5 label "v=200Mb"
$ns duplex-link-op $n4 $n6 label "v=1Gb"
$ns duplex-link-op $n5 $n6 label "v=100Mb"
$ns duplex-link-op $n6 $n2 label "v=40Mb"
$ns duplex-link-op $n4 $n3 label "v=10Mb"


#Adjust first queue
$ns queue-limit $n0 $n4 2098 ;# So that the initial packet is not dropped in the source node - minimum value for a 2MB pkt

# Create primary traffic (will be the red traffic)
if { $protocol == "tcp" } {
	# Create a TCP connection between Server 1 and Receiver 1
	set tcp0 [$ns create-connection TCP $n0 TCPSink $n2 1]

	$tcp0 set window_ $tcp_window
	$tcp0 set fid_ 1 ;# flow id for TCP

	#Send traffic through TCP
	set cbr0 [new Application/Traffic/CBR]
	$cbr0 set packetSize_ 2097152 ;# o primeiro pacote é sempre de 40 bytes...
	$cbr0 set maxpkts_ 1 ;#

	$cbr0 attach-agent $tcp0

	} else {
	# Create an UDP connection between Server 1 and Receiver 1
	set udp0 [$ns create-connection UDP $n0 Null $n2 1]
	$udp0 set fid_ 1

	#Send traffic through UDP
	set cbr0 [new Application/Traffic/CBR]
	$cbr0 set packetSize_ 2097152
	$cbr0 set maxpkts_ 1 ;#
	$cbr0 attach-agent $udp0
	}


# Create additional UDP traffic to make congestion (will be the blue and green traffic)

set udp1 [$ns create-connection UDP $n1 Null $n2 2]
$udp1 set fid_ 2
set udp2 [$ns create-connection UDP $n1 Null $n3 3]
$udp2 set fid_ 3

if {$stream_rate != "0"} {
	#Send traffic through UDP
	set cbr1 [new Application/Traffic/CBR]
	$cbr1 set rate_ $stream_rate
	$cbr1 attach-agent $udp1
	#Send traffic through UDP
	set cbr2 [new Application/Traffic/CBR]
	$cbr2 set rate_ $stream_rate
	$cbr2 attach-agent $udp2
	}

# Break connection
if {$break_connection == "yes"} {
	$ns rtmodel-at 0.6 down $n4 $n6
	$ns rtmodel-at 0.7 up $n4 $n6
	}

# Monitoring

#Monitor queue between $n2 (R1) and $n3 (R2)
#set qm [$ns monitor-queue $n2 $n3 stdout 0.01]

#Flow monitors – enable flow monitoring
#set fmon [$ns makeflowmon Fid]
#$ns attach-fmon [$ns link $n0 $n5] $fmon


# When to start and to stop sending

$ns at 0.5 "$cbr0 start"

if {$stream_rate != "0"} {
	$ns at 0.5 "$cbr1 start"
	$ns at 0.5 "$cbr2 start"
	}
$ns at $simulation_time "finish"

# Define simulation start speed
$ns set-animation-rate 0.8ms

# Start the simulation
$ns run
