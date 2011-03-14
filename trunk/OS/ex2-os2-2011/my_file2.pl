#!/usr/bin/perl -w

# Number of reqaier arguments chek
if( $#ARGV != 0 )
{
	die("Wrong number of arguments\n");
}


open(INFILE, "<")  or die("Cannot open file '$ARGV[0]'\n");

#$out_put_file = ($ARGV[0] =~ s/\.c$/doc.c/);
open(OUTFILE, ">$ARGV[0].") or die("Cannot open file '$ARGV[1]' \n");

binmode INFILE;
@input = <INFILE>;

foreach $str(@input){
 $input_str .= $str;
}

print "Input file len:" .length($input_str) . "\n";
#CommentFunction($input_str);
GetFunction($input_str);
#print "Start work with " .$ARGV[0] . "\n";

#print "Have " . @input . " len\n";
#$werd =  <STDIN>;



foreach $line (@in)
{
# Filter wards strings and write them to output letters file
#	@tiud = ($line =~ m/(\/\/)/g);

#	if(@tiud > 0)
#	{
#		print "Found tiyd"  . "\n";
#	}

	chop $line;
#	if($line =~ m/(^[A-Za-z_\d]+\s?\(.*\);)/g)
	if($line =~ m/^.*[A-Za-z]*\s?\(.*\);/g)
	{
		print ">>>>";
		CommentFunction($line);
	}
	else
	{
		print $line . "\n";
	}
	
}


sub CommentFunction
{
#print $_[0] . "\n";
	
	@blocks = split(/\n{2,}/,$_[0]);
	
	foreach $block(@blocks)
	{
		#FindNumberSpaces($block);
		print FindNumberSpaces($block) . "/*             */\n" . $block . "\n";
	}
}

sub GetFunction
{ 
	@all_fun = ($_[0] =~ m/(\{(.*)|(\n+)\})/g);
	$c=0;
	print "Start func $all_fun \n";
	foreach $same_fun(@all_fun)
	{
		print $c . " " . $same_fun. "\n";
		$c++;		
	}

}
sub FindNumberSpaces
{
	$ret_str = "";
	for($i=0;$i<length($_[0]);$i++)
	{
		if(substr($_[0],$i,1) eq " ")
		{
			$ret_str.= " ";
		}
		else
		{
			return($ret_str);
		}
	}
}
close INFILE;
close OUTFILE;
