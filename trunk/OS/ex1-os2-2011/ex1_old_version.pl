#!/usr/bin/perl -w

#*EX1:: Making file parsing and distribution components.
#*==========================================================================
#* Writen by: Ilia Gaisinsky,  id: 309480051, login: iliaga
#* and:       Andrey Shamis,   id: 321470882, login: andreysh
#* =========================================================================
## Input: text File.
#*
## Output: 3 text sorted Files and sumery on standart uotput.
	
## Script Description: This sprogram is called input data file.
#* The program will receive through Name of a file which will serve as an
#* input of the program. This file reading program the data. Beyond that the
#* program will receive through her other arguments names
#* Three output files:
#* Output file to send strings of letters that the plan call (input file)
#* (argv [2])
#* (argv [3]) 2. Output file to be sent to the numbers (all types) plan call
#* (Argv [4]) 3. Output file to send junk strings




# Number of reqaier arguments chek
if( $#ARGV < 3 )
{
	die("Not enough arguments\n");
}

# Open 1 input file and 3 output files (cheking for opening include)
open(INFILE, "<$ARGV[0]")  or die("Cannot open file '$ARGV[0]' for reading input\n");
open(OUTLET, ">$ARGV[1]") or die("Cannot open file '$ARGV[1]' for writing letters\n");
open(OUTNOM, ">$ARGV[2]") or die("Cannot open file '$ARGV[2]' for writing numbers\n");
open(OUTGARB, ">$ARGV[3]") or die("Cannot open file '$ARGV[3]' for writing garbeg\n");

# set counter to zero
$garb_count = 0;

# Copy file to aray
@input = <INFILE>;

# Loop every line
foreach $line (@input)
{
	# Filter wards strings and write them to output letters file
	@letters = ($line =~ m/([A-Za-z]+)/g);
	foreach $lett(@letters)
	{
		print OUTLET $lett." ";
	}
	# Filter numbers strings and write them to output letters file
	@numbers = ($line =~ m/([\+-]?\d+\.?\d+|\d+)/g);
	foreach $num(@numbers)
	{
		print OUTNOM $num." ";
	}
	# Cut word and num strings from curent line , also updat letters and 
	# words string counter
	$lett_count += ($line =~ s/([A-Za-z]+)/ /g);
	$num_count  += ($line =~ s/([\+-]?\d+\.?\d+|\d+)/ /g);

	# Filter Garbege strings (from wigth spaces) and write them to output 
	# letters file
	@garbeg = ($line =~ m/(\S+)/g);
	foreach $garb(@garbeg)
	{
		print OUTGARB $garb." ";

		# 
		$garb_count ++;	
	}
	# Puting new line at each output file after writing avery line.
	print OUTLET "\n";
	print OUTNOM "\n";
	print OUTGARB "\n";
}
	# Printing strings counters
	print $lett_count." ";	
	print $num_count." ";
	print $garb_count." \n";

# Close opened file
close INFILE;
close OUTLET;
close OUTNOM;
close OUTGARB;


