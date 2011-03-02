#!/usr/bin/perl -w

# -w for warnning


#parameters of input of the program like in c
print "$ARGV[0] \n";               #must be in UPCASE LETTERS
print "@ARGV \n";                   #print all the context of the array

$str = "hi \n bye \n";             
print $str;

$str1 = 'hi \n bye';             #lo mefaaneah et ha \n
print $str1;

$cmd = `ls -l`;           #put all the command uotput to this var.
print $cmd;

#####################################################
# work with files
#####################################################

##### input files ########

#how to read from the standarn input
$in = <STDIN> ;
print "in: $in\n";

open( FL, "\etc\password");   #FL must be upercase - it is the file discriptor

open( FL, "\etc\password") || die("error1");   # errors check (like if)

$line = <FL>;   # only 1 string = cant get lines or chars
@line = <FL>;   # array of strings = can get a line but cant get an char

close(FL);

foreach $l (@lines) {
    print "l: $l\n";           #prints rows of the file
}
print "@line\n";

#######  output files ###############

open( FL, ">/tmp/a") || die("error1");    #open file for write
                                         # > for open a new one (delete all context if the file exist)
                                         # >> add to file
print FL "to file\n";

print STDERR "to file\n";         #to print to stderr

############################################################
#########  split
############################################################

$str = "Igor9Govorovo9DLLL";
@ary = split("9", $str);
print "$ary[0] $ary[1] $ary[2]\n";