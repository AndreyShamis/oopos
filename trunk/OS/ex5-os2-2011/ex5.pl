#!/usr/bin/perl -w

use IO::Zlib;						#need for open gz file
use Data::Dump qw(dump);			#used for indication what is in hash

$gzfile = new IO::Zlib;				#need for open gz file

my $counter = 0;
my %HoH = () ;
my $MAX_DATA = 100;

my $alg_type = $ARGV[3] + 0;

if($alg_type <1 || $alg_type >4)
{
	print "Please set correct data for algorithm type number \n";
	print "\t The correct value is between 1..4 \n";
	exit;
}
else
{
	print "Using Algorithm num: $alg_type\n";

}
#try to open the file file for reading
if ($gzfile->open("DAS2-fs1-2003-1.swf.gz", "r")) 
{
	@data = <$gzfile>;		#get conntent into array of lines
	
	#	for each line
	foreach $line(@data)
	{
		#	This block of code is for comments
		if(substr($line,0,1) ne ';' && $counter == 0)
		{
			$counter = 1;
		}

		# if caoming to end of comments
		if($counter>0)
		{
			$string =  $line;				# get the line
			$string =~ s/^\s+//; 			# clear spaces on the start of str
			
			my (
					$jobNumber, 			#	Jub Number
					$Submit, 				#	Submit
					$wait,					#	wait
					$runtime, 				#	Run time
					$procalloc, 			#	Proc allocate
					$cpuused, 				#	cpu used
					$memused,				#	memory used
					$procreq,				# 	proc req
					$userest,				#	user est
					$memreq,				#	memory req
					$status,				# 	the status
					$uid,					#	uID
					$gid,					#	gID
					$exenum,				#	exe num
					$qnum,					#	q num
					$partition,				#	partiotion
					$prevjob,				#	previous job
					$thinktime				#	Think time
				)
				=	split(/\s+/,$string);
			$counter++;						#	Increase counter
			$HoH{'Process' . $jobNumber} = 
			{
				'jobNumber' 	=> $jobNumber,	
				'submit' 		=> $Submit,
				'wait' 			=> $wait,
				'runtime' 		=> $runtime,
				'procalloc' 	=> $procalloc,
				'cpuused' 		=> $cpuused,
				'memused' 		=> $memused,
				'procreq' 		=> $procreq,
				'userest' 		=> $userest,
				'memreq' 		=> $memreq,
				'status' 		=> $status,
				'uid' 			=> $uid,
				'gid' 			=> $gid,
				'exenum' 		=> $exenum,
				'qnum' 			=> $qnum,
				'partition' 	=> $partition,
				'prevjob' 		=> $prevjob,
				'thinktime' 	=> $thinktime,
			};
			
		}

		#	This block give to program take only MAX_DATA lines
		if($counter > $MAX_DATA && $MAX_DATA != 0)
		{
			last;			#	exit from loop
		}
	}
	$gzfile->close;		#	close file
}
else
{
	# if can not open file
	print "Can not open the file\n";
}	
	
	
#	print dump(%HoH);		#	used for see the Hash of Hash

my $sys_time = 0;
my $memory_size = $ARGV[2];
my $memory_used = 0;

my $processors_size = $ARGV[1];
my $processors_used = 0;


my @processor;

for($i=0;$i<$processors_size;$i++)
{
	$processor[$i] = '0';

}


sub FindFreeProc
{
	for($i=0;$i<$processors_size;$i++)
	{
		if($processor[$i] eq '0')
		{
			#print "dsdsdsd\n";
			return($i);
		}
		
	}	
	return(-1);
}
print "Mem size: $memory_size\n";
print "Number of processors: $processors_size\n";
sub LoadNewProces
{
	$mem_need = int($_[1]);
	#print $_[0] . "\n";
	if($memory_size - $memory_used - $mem_need >=0 && $processors_used<$processors_size)
	{
		$new_proces_proc = FindFreeProc();
		if($new_proces_proc>=0)
		{
#			$processor[$new_proces_proc] = $_[0];
			$processor[$new_proces_proc] = $_[2];
			$processors_used++;
			$memory_used+= $mem_need;
			if($HoH{$processor[$i]}{'thinktime'} != 0)
			{
				$HoH{$processor[$i]}{'thinktime'}=0;
				print "Start $_[0] $sys_time\n"; 
			
			}
			else
			{
				print "Run $_[0] $sys_time\n";
			}
			return(1);
		}
		else
		{
			#print "Error\n";
			return(0)
			#print "Error\n";
		}
	}
}

if($ARGV[3] == 1)
{
	TakeCicle();
}


sub TakeCicle
{
	$da = 1;
	$loop_counter = 0;
	
	while($da)
	{
		$sys_time++;
	   	$da =0;
		foreach $key (sort {$HoH{$a}{"submit"} <=> $HoH{$b}{"submit"}} (keys(%HoH))) 
		{
	   		$mem_needed = rand($memory_size/100);
		  	if($HoH{$key}{"runtime"}>0 )
		  	{
		  		if(LoadNewProces($HoH{$key}{"jobNumber"},$mem_needed,$key) == -1)
		  		{
		  			last;
		  		}
			}
			if($memory_used >= $memory_size)
			{
				last;
			}
	  	}
	  
		foreach $key (sort {$HoH{$a}{"submit"} <=> $HoH{$b}{"submit"}} (keys(%HoH))) 
		{
		  	if($HoH{$key}{"runtime"}>0 )
		  	{
				$da=1;	
				last;
			}
	  	}
  
		print "Mem used $memory_used \t Processors used $processors_used \t";
		print "Idan: $loop_counter\n\n";

		for($i=0;$i<$processors_size;$i++)
		{
			if($processor[$i] ne '0')
			{
				$HoH{$processor[$i]}{'runtime'}-=1;
				if($HoH{$processor[$i]}{'runtime'} == 0)
				{
					print "END $HoH{$processor[$i]}{'jobNumber'} $sys_time \n";
				}
				$processor[$i] = '0';		
			}
	
		}	
		
		$processors_used 	= 	0;
		$memory_used 		= 	0;
		$loop_counter++;

	}
}



	foreach $key (sort {$HoH{$a}{"submit"} <=> $HoH{$b}{"submit"}} (keys(%HoH))) 
	{

	  	if($HoH{$key}{"runtime"}>0 )
	  	{
			print "Bad \n";	
			last;
		}
  }
  
