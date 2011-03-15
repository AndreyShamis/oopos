#!/usr/bin/perl -w

# Number of reqaier arguments chek
if( $#ARGV != 0 )
{
	die("Wrong number of arguments\n");
}




#==============================================================================
#	Open files block code
open(INFILE, "<$ARGV[0]")  or die("Cannot open file '$ARGV[0]'\n");
#$out_put_file = $ARGV[0] ;
#$out_put_file =~ s/\.c$/.doc.c/;
$out_put_file = CreateOutputFileName($ARGV[0]);
#print $out_put_file . "\n";
open(OUTFILE, ">$out_put_file") or die("Cannot open file $out_put_file \n");
#	End open files block


#==============================================================================
#binmode INFILE;
@input = <INFILE>;
##============== Put array into string
#foreach $str(@input){
# $input_str .= $str;
#}
##====================================

#print "Input file len:" .length($input_str) . "\n";
#CommentFunction($input_str);
#GetFunction($input_str);
#print "Start work with " .$ARGV[0] . "\n";

#print "Have " . @input . " len\n";
#$werd =  <STDIN>;

$status = 0;
$sub_seger = 0;
$pdf_ouput=""; 
$pdf_counter=0;
foreach $line (@input)
{
	chop $line;		# delete \n on the end

	#if($line =~ /^\s*$/ && 2==3)
	#{
		
	#}
	#else
	#{
		if($status == 0 || $status == 1)
		{
			if($line =~ /^\s*#include\s*.*/)
			{
				
				#$line = $line . "\t/* " . GetCommentStr($line) . " */\n";
				print  $line . "\n";
				$status = 1;
			}
			else
			{
				$status =2;
				#print "Convert status to 2\n\n";
			}
		}
		elsif($status < 4)#if($status == 2 || $status == 3)
		{
			#	Variables AGDAA
			if($line =~ /^\s*\w+\s+\w+.*[^)];\s*$/)
			{
				#$line = $line . "\t/* " . GetCommentStr($line) . " */\n";
				$status = 3;
				print "$line \n";
			}
			else
			{
				$status = 3;
				#print "End of comm variables\n\n";
			}
			
			# Function AGDARA
			if($line =~ /^\s*\w+\s+\w+.*\(.*\);$/)
			{
				#$line = $line . "\t/* " . GetCommentStr($line) . " */\n";
				$status = 3;
				print "$line \n";			
			}
			else
			{
				$status = 3;
				#print "End of comm Function\n\n";
			}
		}
		
		if($status == 5)
		{
			if($line =~ /\{/)
			{
				$sub_seger++;
				#print "+Seger $sub_seger\n";
			}
			if($line =~ /\}/)
			{
				$sub_seger--;
				#print "-Seger $sub_seger\n";
			}		
			if($sub_seger == 0 && $status == 5)
			{
				#print "Exit from Main";
				$status = 6;
			}
			if($line =~ /^\s*\w+\s+\w+.*[^)];\s*$/)
			{
				#$line = $line . "\t/* " . GetCommentStr($line) . " */\n";
				#print "Found Variable in Main\n $line \n";
			}
		}

		
		if($status == 5)
		{
			
		}
		
		if($line =~ /int main\s*\(.*\)/)
		{
			print "Comment to main\n";
			

			$status = 5;
		}
		
		#	looking for enother function
		if($status == 6)
		{
			
			print "\n";
			
			#	Start define function variables 
			if($line =~/^\s*\w+\s+\w+.*\(.*\)$/)
			{
				$status = 7;
				$vars = $line;
				$vars =~ s/^.*\(//;
				$vars =~ s/\)//;
				print "Enter to function\n";
				
				$function_get = "/* \n * The function get:\n";
				
				
				@func_var = split(/,/,$vars);
				
				foreach $variable(@func_var)
				{
					$function_get.= " *\t". $variable . " \t-  " . GetCommentStr("What is the parameter? " . $variable) . "\n";
					print "Variable \t\t $variable \n";
				}
				#$function_get.="*/";
				
				$function_ret = " *\n * The function return:\n * \t" . GetCommentStr("What function return?") . " \n";
				$function_perf = " *\n * function performs the following steps:\n * \t" . GetCommentStr("What this function do?") . " \n */\n";
				
				$line = $function_get . $function_ret . $function_perf . $line;
				$pdf_ouput[$pdf_counter] = $function_get . $function_ret . $function_perf;
				$pdf_counter++;
			}
		}
		
		#	Looking for another function variable
		if($status == 7 || $status == 8)
		{
			
			if($line =~ /^\s*\w+\s+\w+.*[^)];\s*$/ && $status ==8)
			{
				print "\n$line\n";
				#$line = $line . "\t/* " . GetCommentStr($line) . " */\n";
			}

			
			if($line =~ /\{/)
			{
				$status = 8;
				$sub_seger++;
				#print "+Seger $sub_seger\n";
			}
			elsif($line =~ /\}/)
			{
				$sub_seger--;
				#print "-Seger $sub_seger\n";
			}	
			
			if($sub_seger == 0 && $status == 8)
			{
				print "Exit from Function";
				$status = 6;
			}
			
		}
		
		
	#}


#	if($line =~ m/(^[A-Za-z_\d]+\s?\(.*\);)/g)
#	if($line =~ m/^.*[A-Za-z]*\s?\(.*\);/g)
#	{
#		print ">>>>";
#		CommentFunction($line);
#	}
#	else
#	{
#		print $line . "\n";
#	}

		
}
print "----------------------------------------------------\n";
foreach $line (@input)
{
	print $line . "\n";
}


use PDF::Create;

    my $pdf = new PDF::Create('filename' => 'mypdf.pdf',
                              'Version'  => 1.2,
                              'PageMode' => 'UseOutlines',
                              'Author'   => 'Andrey Shamis & Ilia Gaisinsky',
                              'Title'    => '$ARGV[0]',
                         );
    my $root = $pdf->new_page('MediaBox' => [ 0, 0, 612, 792 ]);

    # Add a page which inherits its attributes from $root
    my $page = $root->new_page;

    # Prepare 2 fonts
    my $f1 = $pdf->font('Subtype'  => 'Type1',
                        'Encoding' => 'WinAnsiEncoding',
                        'BaseFont' => 'Helvetica');
    # Prepare a Table of Content
    my $toc=$pdf->new_outline('Title'=>'Document','Destination'=>$page);

    #$page->stringc($f1, 20, 306, 396, "2");
	$c = 0;
	print "PDF counter\n".$pdf_counter . "\n";
	$page_margin = 10;
	$page_fint_size = 12;
	$page->stringl($f1, 12, $page_fint_size, 772,"/* Main program:");
	$page->stringl($f1, 12, $page_fint_size, 759,
								" *     Using the various functions");
	$page->stringl($f1, 12, $page_fint_size, 747," */");

	foreach $line(@pdf_ouput)
	{
		@vals = split(/\n/,$line);
		
		foreach $ll(@vals)
		{
			$ll =~s/\t/    /;				# space manipulation
			$page->stringl($f1, 12, $page_margin, 700+$c,$ll);
			$c-=12;
		}
	}
    # Add the missing PDF objects and a the footer then close the file
    $pdf->close;
#==============================================================================
sub CommentFunction
{
#print $_[0] . "\n";
	
	#@blocks = split(/\n{2,}/,$_[0]);
	
	#foreach $block(@blocks)
	#{
	#	#FindNumberSpaces($block);
	#	print FindNumberSpaces($block) . "/*             */\n" . $block . "\n";
	#}
	print "\n";
}
#==============================================================================
sub GetFunction
{ 
	@all_fun = ($_[0] =~ m/(\{(.*)|(\n+)\})/g);
	$c=0;
	print "Start func \n";
	foreach $same_fun(@all_fun)
	{
		print $c . "-" . $same_fun. "\n";
		$c++;		
	}

}
#==============================================================================
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

#==============================================================================
close INFILE;
close OUTFILE;

#==============================================================================
# Function which get input file name and convert the name to same name with
# sub-sufix.
# Example	my_file.c ==> my_file.doc.c
# Return created name
sub CreateOutputFileName
{
	$out_put_file = $_[0] ;				#	Read input file name

	$out_put_file =~ s/\.c$/.doc.c/;	#	Replacing needed by sufix
	
	return($out_put_file);				#	return value
}

#==============================================================================
#	Function which egt some string and ask from user which 
#	comment need to write.
#	Return comment string
sub GetCommentStr
{
	print "Please write comment for: " . $_[0] . ". And press enter\n";
	$comment = <STDIN> ;
	chop $comment;
	return($comment);
}