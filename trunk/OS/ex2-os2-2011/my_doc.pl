#!/usr/bin/perl -w

# Number of reqaier arguments chek
if( $#ARGV != 0 )
{
	die("Wrong number of arguments\n");
}

#==============================================================================
#	Open files block code
#	Open input file
open(INFILE, "<$ARGV[0]")  or die("Cannot open file '$ARGV[0]'\n");
#	Create file name for output
$out_put_file = CreateOutputFileName($ARGV[0]);	
#	Create file name for output file in pdf
$pdf_file_name= GetPdfFileName($ARGV[0]);
#	End open files block


@input = <INFILE>;			# get input into array
close INFILE;				# Close inout file

my $input_str;
#	Load all array values into string for searching included comments
foreach $str(@input)
{
	$input_str .= $str;		#	Loading to one string
}

#	Looking for comments
if($input_str =~ /\s*\/\/.*/ || $input_str =~ /\s*\;?\s*\/\/\s*/ || $input_str =~ /^\s*\/\*/ || $input_str =~ /.*;?\s*\/\*/)
{
	#	Found comments - EXIT
	exit;
}

#	Open file name for output
open(OUTFILE, ">$out_put_file") or die("Cannot open file $out_put_file \n");

#==============================================================================
#	Variables used
my $status 		= 	0;				#	Parser status
my $sub_seger 	= 	0;				#	Multi Brackets counter
my $pdf_ouput	=	""; 			#	Pdf output data
my $pdf_counter	=	0;				#	Pdf number function be printed
my $main_start 	= 	0;				#	Line number of start main function
my $main_end	=	0;				#	Line number of end function
my $line_indicator	=	0;			#	Line counter

#==============================================================================
#	Starting search by line line
foreach $line (@input)
{
	chop $line;		# delete \n on the end

	if($status == 0 || $status == 1)
	{
		#Start comment include files
		if($line =~ /^\s*#include\s*.*/)
		{
			$line = $line . "\t/* " . GetCommentStr($line) . " */";
			$status = 1;
		}
		else{	
			$status =2;				# end of comment included files
		}
	}
	elsif($status < 4)
	{
		#	Start comment global variables
		if($line =~ /^\s*\w+\s+\w+.*[^)];\s*$/)
		{
			$line = $line . "\t/* " . GetCommentStr($line) . " */";
			$status = 3;
		}
		
		# Start comment Function defenitions
		if($line =~ /^\s*\w+\s+\w+.*\(.*\);$/)
		{
			$line = "/* " . GetCommentStr($line) . " */\n" . $line ;
			$status = 3;		
		}
	}
	
	if($status == 5)
	{
		# 	Now located in main function
		#	Tryng to dect end of main function
		if($line =~ /\{/){		#	Multi Brackets counter
			$sub_seger++;
		}
		elsif($line =~ /\}/){	#	Multi Brackets counter
			$sub_seger--;
		}		
		
		#	End of main function detected
		if($sub_seger == 0 && $status == 5)
		{
			$main_end = $line_indicator;	# set main end line
			CommentMainByBlocks();			# start work whith comments by block
			$status = 6;
		}
		
		if($line =~ /^\s*\w+\s+\w+.*[^)];\s*$/)
		{
			$line = $line . "\t/* " . GetCommentStr($line) . " */";
			$main_start = $line_indicator+1;# main start counter
		}
	}
	
	if($line =~ /int main\s*\(.*\)/)
	{	#	Starting pearsing main function
		$status = 5;
		$main_start = $line_indicator;
	}
	
	#	looking for enother function
	if($status == 6)
	{		
		#	Start define function variables 
		if($line =~/^\s*\w+\s+\w+.*\(.*\)$/)
		{
			$status = 7;
			$vars = $line;
			$function_name = $line;
			$function_name =~s/\(.*/(...)/;
			$vars =~ s/^.*\(//;
			$vars =~ s/\)//;
			$function_get = "/* \n * The function get:\n";			
			@func_var = split(/,/,$vars);
			foreach $variable(@func_var)
			{
				$function_get.= " *\t". $variable . " \t-  " 
					. GetCommentStr("What is the parameter of function $function_name? " 
					. $variable) . "\n";
			}
			$function_ret = " *\n * The function return:\n * \t" 
				. GetCommentStr("What function $function_name return?") . " \n";
			$function_perf = " *\n * function performs the following steps:\n * \t" 
				. GetCommentStr("What this function($function_name) do?") . " \n */\n";	
				
			$line = $function_get . $function_ret . $function_perf . $line;
			$pdf_ouput[$pdf_counter] = $function_get . $function_ret . $function_perf;
			
			$pdf_counter++;
		}
	}
	elsif($status == 7 || $status == 8)
	{	#	Looking for another function variable
		if($line =~ /^\s*\w+\s+\w+.*[^)];\s*$/ && $status ==8)
		{
			$line = $line . "\t/* " . GetCommentStr($line) . " */";
		}

		if($line =~ /\{/){			#	Multi Brackets counter
			$status = 8;
			$sub_seger++;
		}
		elsif($line =~ /\}/){		#	Multi Brackets counter
		
			$sub_seger--;
		}	
		if($sub_seger == 0 && $status == 8)	{
			$status = 6;
		}
	}
	
	$line_indicator++;					# increase line counter			
}
#==============================================================================
#	Start output into file
foreach $line (@input)
{
	if($line ne "CLEARED")				# check if the line not cleared
	{
		print OUTFILE $line . "\n";
	}
}
close OUTFILE;

#==============================================================================
#	Creating PDF file
use PDF::Create;

    my $pdf = new PDF::Create('filename' => $pdf_file_name,
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

	$c = 0;
	print "PDF counter\n".$pdf_counter . "\n";
	$page_margin = 10;
	$page_fint_size = 12;
	$page->line(0, 780, 612, 780);
	$page->stringl($f1, 12, $page_fint_size, 762,"/* Main program:");
	$page->stringl($f1, 12, $page_fint_size, 749,
								" *     Using the various functions");
	$page->stringl($f1, 12, $page_fint_size, 737," */");
	$page->line(0, 734, 612, 730);
	foreach $line(@pdf_ouput)
	{
		@vals = split(/\n/,$line);
		
		foreach $ll(@vals)
		{
			$ll =~s/\t/    /;				# space manipulation
			$page->stringl($f1, 12, $page_margin, 700+$c,$ll);
			$c-=12;
		}
		
		$page->line(0, 700+$c, 612, 700+$c);
		$c-=12;
	}
    # Add the missing PDF objects and a the footer then close the file
    $pdf->close;


#==============================================================================
#	Function which get some string from program and counting tabulation
#	from left side. After return string which include needed number of spaces
sub FindNumberSpaces
{
	my $ret_str = "";						# ret value
	for($i=0;$i<length($_[0]);$i++)			# start search
	{
		if(substr($_[0],$i,1) eq " ")		# check for spaces
		{
			$ret_str.= " ";					# put space to start string
		}
		elsif(substr($_[0],$i,1) eq "\t")	# check for tabs
		{
			$ret_str.= "    ";				# change \t to 4 spaces
		}
		else								# found somthing else
		{
			return($ret_str);				# return value
		}
	}
}

#==============================================================================
#	Function for comment main by Blocks
sub CommentMainByBlocks
{
	my $all_main_string = "";
	for($i=$main_start;$i<$main_end;$i++)
	{
		$all_main_string .= $input[$i] . "\n";
		$input[$i]= "CLEARED";
	}
	
	@main_blocks = split(/\n{2,}/,$all_main_string);
	
	$all_main_string = "";
	foreach $main_line(@main_blocks)
	{
		$all_main_string.= "\n".FindNumberSpaces($main_line)."/* " 
			. GetCommentStr(" this main block: \n $main_line \n") 
			. " */\n" . $main_line . "\n";
	}
	
	$input[$main_start] = $all_main_string;
}

#==============================================================================
# Function which get input file name and convert the name to same name with
# sub-sufix.
# Example	my_file.c ==> my_file.doc.c
# Return created name
sub CreateOutputFileName
{
	my $out_put_file = $_[0] ;				#	Read input file name

	$out_put_file =~ s/\.c$/.doc.c/;	#	Replacing needed by sufix
	
	return($out_put_file);				#	return value
}

#==============================================================================
#	Function which get input file name and convert the name to 
#	<file_name>.c => <file_name>.pdf
#	Return the new file name
sub GetPdfFileName
{
	my $out_put_file = $_[0] ;				#	Read input file name

	$out_put_file =~ s/\.c$/.pdf/;	#	Replacing needed by sufix
	
	return($out_put_file);				#	return value
}
#==============================================================================
#	Function which egt some string and ask from user which 
#	comment need to write.
#	Return comment string
sub GetCommentStr
{
	print "Please write comment for:\n" . $_[0] . "\n";
	my $comment = <STDIN> ;
	chop $comment;
	return($comment);
}