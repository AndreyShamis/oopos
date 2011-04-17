#!/usr/bin/perl -w

use IO::Zlib;						#need for open gz file
use Data::Dump qw(dump);			#used for indication what is in hash

$gzfile = new IO::Zlib;				#need for open gz file

my $counter = 0;
my %HoH = () ;
my $MAX_DATA = 10;

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

open(INFILE, "<$ARGV[0]")  or die("Cannot open file '$ARGV[0]'\n");


@data = <INFILE>;		#get conntent into array of lines

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

	
#	print dump(%HoH);		#	used for see the Hash of Hash
###############################################################################
###############################################################################
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

###############################################################################
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
###############################################################################
print "Mem size: $memory_size\n";
print "Number of processors: $processors_size\n";


my %queue = ();


###############################################################################
sub PutProcessReadyToQueue
{
	$proc_ind = $_[0];
	$queue{$proc_ind} = 
	{
		'jobNumber' 	=> $HoH{$proc_ind}{'jobNumber'},	
		'submit' 		=> $HoH{$proc_ind}{'submit'},
		'memreq' 		=> int(rand($memory_size/10)),
		'runtime' 		=> $HoH{$proc_ind}{'runtime'},
		'number'		=> $sys_time,
		'runed'			=> 0,
		'wait' 			=> 0,
	};
}

###############################################################################
sub GetSome
{
	foreach $key (sort {$queue{$a}{"number"} <=> $queue{$b}{"number"}} (keys(%queue))) 
	{

	  	if($queue{$key}{"runed"} == 0 )
	  	{
	  		return($key);
		}
  	}
  	
  	return(0);

}

###############################################################################
sub GetSome2
{
	foreach $key (sort {$queue{$a}{"runtime"} <=> $queue{$b}{"runtime"}} (keys(%queue))) 
	{

	  	if($queue{$key}{"runed"} == 0 )
	  	{
	  		return($key);
		}
  	}
  	
  	return(0);

}

###############################################################################
sub GetSome3
{
	foreach $key (sort {$queue{$a}{"memreq"} <=> $queue{$b}{"memreq"}} (keys(%queue))) 
	{

	  	if($queue{$key}{"runed"} == 0 )
	  	{
	  		return($key);
		}
  	}
  	
  	return(0);

}
###############################################################################
sub LoadFromQueueToProcessor
{
	while($processors_used < $processors_size)
	{
		$processor_free = FindFreeProc();
		if($processor_free >=0)
		{


		
			if($alg_type == 1)
			{
				$betoken = GetSome();
			}
			elsif($alg_type == 2)
			{
				$betoken = GetSome2();
			}
			elsif($alg_type == 3)
			{
				$betoken = GetSome3();
			}
			elsif($alg_type == 4)
			{

			}
			
			if($betoken &&  $queue{$betoken}{"memreq"} <= $memory_size-$memory_used)
			{
				$memory_used+=$queue{$betoken}{"memreq"};
				$queue{$betoken}{"runed"} = 1;
				$processor[$processor_free] = $betoken;
				$processors_used+=1;
				print "Start , " . $queue{$betoken}{'jobNumber'} . " , " . $sys_time . "\n";
			}
			else
			{
				last;
			}
		}
	}
}
###############################################################################
sub UpdateWaitTime
{
	foreach $key ((keys(%queue))) 
	{

	  	if($queue{$key}{"runed"} == 0 )
	  	{
	  		$queue{$key}{"wait"}+=1;
		}
  	}

}
###############################################################################
sub CountProcessNeedToWork
{

	$counter=0;
	foreach $key ((keys(%queue))) 
	{
	  	if($queue{$key}{"runtime"} >0 )
	  	{
	  		$counter++;
		}
  	}
  	return($counter);
 
}
###############################################################################
sub ProcessorWork
{
	if($processor[$_[0]] ne '0')
	{
		$queue{$processor[$_[0]]}{"runtime"} -=1;
		if($queue{$processor[$_[0]]}{"runtime"} <= 0)
		{
			$memory_used-=$queue{$processor[$_[0]]}{"memreq"};
			print "END , " . $queue{$processor[$_[0]]}{"jobNumber"} . " , " . $sys_time . "\n";
			
			#delete $queue{$processor[$_[0]]};
			
			$processors_used-=1;
			$processor[$_[0]] = '0';
		}
		else
		{
			print "Run , " . $queue{$processor[$_[0]]}{"jobNumber"} . " , " . $sys_time . "\n";		
		}
	}
}

###############################################################################
sub allProcWork
{
	#print "Start Run all process\n";
	for($i=0;$i<$processors_size;$i++)
	{
		ProcessorWork($i);
	}
}
###############################################################################
my $process_counter=0;
	$have_todo = 1;
while($have_todo)
{
		
		
	foreach $key (sort {$HoH{$a}{"submit"} <=> $HoH{$b}{"submit"}} (keys(%HoH))) 
	{

		
		if($HoH{$key}{"submit"} > $sys_time)
		{
			last;
		}
	  	if($HoH{$key}{"submit"} == $sys_time)
	  	{
	  		$process_counter++;
			PutProcessReadyToQueue($key);
			delete $HoH{$key};
			#last;
		}

  	}		

	LoadFromQueueToProcessor();
	allProcWork();
	UpdateWaitTime();
	$rrr = CountProcessNeedToWork();
#	print "Mem used $memory_used \t Processors used $processors_used \t";
#	print "Idan: $sys_time \t Last $rrr\n\n";

	$sys_time++;

	if(keys (%HoH) == 0 && $rrr == 0)
	{
		$have_todo = 0;
	}
}

	$wait_time = 0;
	foreach $key ((keys(%queue))) 
	{

	  	$wait_time+=$queue{$key}{"wait"} ;
	  	
  	}

	print "Wait time is : ". $wait_time/$process_counter ." \n";

	foreach $key (sort {$HoH{$a}{"submit"} <=> $HoH{$b}{"submit"}} (keys(%HoH))) 
	{

	  	if($HoH{$key}{"runtime"}>0 )
	  	{
			print "Bad \n";	
			last;
		}
  	}
  
