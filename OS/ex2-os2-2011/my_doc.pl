#!/usr/bin/perl -w

# Number of reqaier arguments chek
if( $#ARGV != 3 )
{
	die("Wrong number of arguments\n");
}

# Open input and output files (cheking for opening include)
open(INFILE, "<$ARGV[0]")  or die("Cannot open file '$ARGV[0]'\n");
open(OUTFILE, ">$ARGV[1]") or die("Cannot open file '$ARGV[1]' \n");


@input = <INFILE>;