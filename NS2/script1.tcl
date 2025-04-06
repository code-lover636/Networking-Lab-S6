# Prints hello
puts hello
puts stdout "Hello, world!"
puts "Hello World!" 
puts "Hello\nWorld"
puts {hello world}

# Multi-line comment
if 0 {
   my first program in Tcl program
   Its very simple
}

puts [expr 3 + 2] ;# print sum of the 3 and 2


# Variable assignment
set a 3
puts $a

set myVariable 18
puts [expr $myVariable + 6 + 9]

set myVariable "hello world"
puts $myVariable
set myVariable {hello world}
puts $myVariable


set {variable B} test
puts ${variable B}

# List
set myVariable {red green blue}
puts [lindex $myVariable 2]
set myVariable "red green blue"
puts [lindex $myVariable 1]


# Associative array (hashmap)
set  marks(english) 80
puts $marks(english)
set  marks(mathematics) 90
puts $marks(mathematics)

# print size
puts [array size marks]
# File handling
set myfile [open "script1.tcl" r]


# Dynamic Typing
set variableA "10"
puts $variableA
set sum [expr $variableA +20];
puts $sum

# IF statement

set a 10

set a 100

if { $a == 10 } {
   puts "Value of a is 10"
} elseif { $a == 20 } {
   puts "Value of a is 20"
} elseif { $a == 30 } {
   puts "Value of a is 30"
} else {
   puts "None of the values is matching"
}

puts "Exact value of a is: $a"


# Switch

set grade B;

switch $grade {
   A {
      puts "Well done!"
   }
   B {
      puts "Excellent!"
   }

   C {
      puts "You passed!"
   }
   F {
      puts "Better try again"
   }
   default {
      puts "Invalid grade"
   }
}
puts "Your grade is  $grade"


# Loop

set a 10

while { $a < 20 } {
   puts "value of a: $a"
   incr a;
}

for {set a 30} {$a > 20} {incr a -5} {
    puts "value of a: $a"
}