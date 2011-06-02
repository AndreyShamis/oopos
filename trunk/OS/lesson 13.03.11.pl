

## מערך אסוציאטיבי / map / hash

# hash coins is must be with %
# "Quarter" - it is the name of the cell, 25 - the value of the cell
%coins = ("Quarter", 25, "Dime", 50, "Nickel", 5) ;

#to print a content of the cell
print "$coins{Nickel}\n");

#to add key with value
$coins{"shekel"} = 0 ;

#print all contnt of the hash variable
while( ($key,$val)=each(%coins)) {
    
    print "$key: $vslue";
}

foreach $key (keys %coins) {
    print "$key: $coins{$key}\n";
}
# to sort by keys (by abc)
foreach $key sort=(keys %coins){
    print "$key: $coins{$key}\n";
}

#######################################################
## refernce ("pointer")

# a function that get as the first variable a refence
sub foo {
    $v1 = shift ;
    
    #print the content of refence v1
    print "$$v1 \n";
    #change the value
    $$v1 = 90 ;
}

$val = 5 ;
#send a refernce to val (with \)
foo(\$val);

####### refernce to array
sub foo1 {
    $ary_ref = shift ;
    
    #casting to array
    print "@$ary_ref\n";
    push @$ary_ref, "sss";
    print "#ary_ref->[0] \n"; # to get to cpecific cell
}

@array = ( 5,8);
for1(\@array ) ;

############# refernce to hash

sub foo2 {
    my $hash_ref = shift ;
    print "$hash_ref->{"one"}\n";
}

%hash = ("one",1) ;
foo2(\%hash);

###############################################################
## libraries


# (prel module) שם הקובץ ב pm


#### my_lib.pm - name of the file

package my_lib

use strict ;
use exporter; #for the functions to be public - everyone can use them

my $version = 10 ;

@ISA = qw(Exporter);

@Exporter_ok = qw( func1 func2 ) ; # what function will be public
                                    # qw it adds " ' " and " , " ... it must be     @Exporter_ok = ('func1', 'func2') ;
sub func1{
    return 1;
}

sub func2 {
    return 2;
}

1;  ## MUST BE 1 - BECAUSE IT IS THE RETURN VALUE


#################### use this library

#!/usr/lib/perl -w

use my_lib

print "func1() \n";

######################################################################
## example read from file to double hash

#!/usr/lib/perl -w

my %HoH = () ;
my $file = "/etc/password";

open( PWD , $file );

while( <PWD> ){                                                   #it run through the lines of the file- each loop the variable $_ contains the line
    my ($login, $pass, $uid, $gid, $v, $dir, $shell)=split(/:/);  # it splits the variable $_ (-it is line from the file)
    
    $HoH{ $login }{'vid'} = $uid ;
    $HoH{$login}{'pid'} = $gid ;
    $HoH{$login}{'dir'} = $dir ;
}

