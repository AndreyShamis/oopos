#!/usr/bin/perl -w

use strict;

my $str = "100aaa123";
if ($str =~ /^\d+aaa\d+$/) {
    print "There is numbers!\nfirst: $1, second: $2\n";
}else{
    print "No numbers\n";
}


$str =~ m/(^(\d+)$)/
print $str;


#subtitude all 'a' with 'k'

$str =~ s/a/k/g;   # s = subtitud // g = global to replace all the 'a' with 'k' (and not only the first)
print $str;

$str =~ s/a{3}/k/g;   # a{3} - means "aaa" - that what it will replace // g - means all shows of "aaa"

$str =~ s/a{2,4}/k/; # a{2,3} - means all showsof "aa" "aaa" "aaaa"

###########################################
# summmary

# * - zero or more
# + - one or more
# ? - zero or one
# {x} - x shows
# {x,y} - from x to y shows
# ( ) - match, the match will enter to $1, $2,...

# \d - digit
# \D - every thing that not is digit
# \w - word
# \W - anything that no word
# \s - white spaces

##################################
## two options with split

@org = split("aaa",$str);
@org = split(/[ \+]/, $str)

####################################
## Functions

sub my_func1 {                                # will not enter this function till the program will cat it
    
    my $var1 = shift;  # will take the first delete it from original array and return it to var1
    my $var2 = shift; 
    
    print "v1: $var1 v2:$var \n";
    
    print "$_[0] \n";
    print "$_[1] \n";
    
    print "in func1\n";
}

my_func1( 123, "aaa");

