#!/usr/bin/perl -w
###############################################################################
#	Students of Hadassah College 
#				Andrey Shamis		andreysh
#				Ilia Gaysinsky		iliaga
#
###############################################################################
#		This script provide tools for what was explained on labaratory.       #
#	The script getting file name for the log file and in next(second parameter)
#	need provide number of CPU be used(importand to loock in the log file for
#	know how many CPU`s you need to use.Thats mean how many CPU the process
#	can ask for), i thirt parameter need provide the memory size and in last
#	one you must provide algorithm number for check. The value can be 
#	between 1-4.
###############################################################################
#use Data::Dump qw(dump);			#used for indication what is in hash

print "Наченаем мозгаёбку. Срать кирпичами запрещенно!\n";

my $counter = 0;						#	counter used in how manu lines read
my %HoH = () ;							#	Hash for input data

#	For limit the number lines be readed set this value to how many process
#	you want to load. If you not intereseted in this just set the value be 0.
my $MAX_DATA = 500;					

my $processors_size = $ARGV[1];			#	Number of CPU
my $memory_size 	= $ARGV[2];			#	Memory max size
my $alg_type 		= $ARGV[3]+0;		#	Algorithm type

#	Check how many parameters was provided by user.
if($#ARGV != 3)
{
	print "Please enter correct data:\n" ;
	print "\t<INPUT FILE NAME> <CPU NUMBER>";  
	print " <MEMORY SIZE> <NUMBER OF ALGORITHM>\n";
	exit;
}

#	Check if the algorithm type in range of posible variation
if($alg_type <1 || $alg_type >4)
{
	print "Please set correct data for algorithm type number \n";
	print "\t The correct value is between 1..4 \n";
	exit;
}

#	Check how many CPU user want to use in test. The minimum is 1 but you
#	will se that the minimum is the maximum of number CPU about what some
#	process can use.
if($processors_size < 1)
{
	print "Please enter number of CPU more than 0\n";
	exit;
}

#	Memory check section. User must provide min 1 .
if($memory_size < 1)
{
	print "Please enter memory size more than 0\n";
	exit;
}

#	Open log file for reading
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
		if($jobNumber == 0)
		{
			last;
		}
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

close INFILE;						#	Close opened file

###############################################################################
###############################################################################
my $sys_time = 0;					#	Variable for system time
my $memory_used = 0;				#	Memory used in some moment
my %queue = ();						#	Queue for process
my %completed = ();	

my $processors_used = 0;			#	Number of used CPU
my $cpu_util	=	0;				#
my $proc_usage 	= 	0;				#
my @processor;						#	Processors structure

#my $counter_proc_loaded		=	0;	#	Number of proc started
#my $counter_proc_finished	=	0;	#	Number of proc ended

#	Loading start informtion into processors
for($i=0;$i<$processors_size;$i++)
{
	$processor[$i] = '0';
}

###############################################################################
#	Function wich detecting number of CPU which not used and return him
#	If no free CPU return negative number
sub FindFreeProc
{
	for($i=0;$i<$processors_size;$i++)
	{
		if($processor[$i] eq '0')	#	Check if processor busy
		{
			return($i);				#	Return id of free CPU
		}
	}	
	return(-1);						#	Return negative		
}

###############################################################################
#	Function wich puting process into queue
#	Geting hash key
sub PutProcessReadyToQueue
{
	$proc_ind = $_[0];			#	Process hash key
	$queue{$proc_ind} = 
	{
		'jobNumber' 	=> $HoH{$proc_ind}{'jobNumber'},	#	Job number	
		'submit' 		=> $HoH{$proc_ind}{'submit'},		#	Submit time
		'memreq' 		=> int(rand($memory_size)),			#	Memory need
		'runtime' 		=> $HoH{$proc_ind}{'runtime'},		#	Run time
		'number'		=> $sys_time,						#	Start time
		'runed'			=> 0,								#	Not runed
		'wait' 			=> 0,								#	Wait time
		'procalloc'		=> $HoH{$proc_ind}{'procalloc'},	#	Number of CPU
	};
	
	print "Start,\t" . $HoH{$proc_ind}{'jobNumber'} . ",\t" . $sys_time . "\n";
}


###############################################################################
#	Function for check if process have number of free CPU`s for run
#	Geting number of needed CPU`s
#	Return true if have or false else
sub HaveenoughProc
{
	#	Cheking 
	if($processors_size - $processors_used >= $_[0])
	{
		return(1);					#	Return true
	}
	
	return(0);						#	Dont have free cpu
}

###############################################################################
#	Function which check if some process can run in this time
#	Function get the key of process and check if the process can get
#	enough CPU and get enough memory and also if the process waiting
#	If the all condition success return true, else return false
sub CheckPosibilityToRun
{
	if($queue{$_[0]}{"runed"} == 0 
		&& HaveenoughProc($queue{$_[0]}{"procalloc"}) 
		&& $queue{$_[0]}{"memreq"} <= $memory_size-$memory_used)
	{
		return(1);					#	return true
	}
	return(0);						#	return false
}

###############################################################################
#	First algorithm
sub FirstComeFirstServed
{
	foreach $key(sort{$queue{$a}{"number"}<=>$queue{$b}{"number"}}(keys(%queue))) 
	{
		if(CheckPosibilityToRun($key)){
	  		return($key);
		}
  	}
  	
  	return(0);

}

###############################################################################
sub SmallestJobFirst
{
	foreach $key (sort {$queue{$a}{"procalloc"} <=> $queue{$b}{"procalloc"}} (keys(%queue))) 
	{
	  	if(CheckPosibilityToRun($key)){
	  		return($key);
		}
  	}
  	
  	return(0);

}

###############################################################################
sub BiggestJobFirst
{
	foreach $key (sort {$queue{$b}{"procalloc"} <=> $queue{$a}{"procalloc"}} (keys(%queue))) 
	{
		if(CheckPosibilityToRun($key)){
	  		return($key);
		}
  	}
  
  	return(0);

}

###############################################################################
sub ShortestJobFirst
{
	foreach $key (sort {$queue{$a}{"runtime"} <=> $queue{$b}{"runtime"}} (keys(%queue))) 
	{
	  	if(CheckPosibilityToRun($key)){
	  		return($key);
		}
  	}
  	
  	return(0);

}
###############################################################################
#	Function which trying to load to CPU some process which located
#	in queue. If fail exit from the function becouse no proces can be loaded
#	Its may be produce by no free cpu or no ehuf memory
sub LoadFromQueueToProcessor
{
	#	While have free cpu
	while($processors_used < $processors_size)
	{
		#	Get CPU id be used
		$processor_free = FindFreeProc();
		#	Check if the id is good
		if($processor_free >=0)
		{
			#	Use needed algorithm for check process
			if($alg_type == 1){
				$betoken = FirstComeFirstServed();
			}
			elsif($alg_type == 2){
				$betoken = SmallestJobFirst();
			}
			elsif($alg_type == 3){
				$betoken = BiggestJobFirst();
			}
			elsif($alg_type == 4){
				$betoken = ShortestJobFirst();
			}
			
			#	Check if good process selected
			if($betoken)
			{
				#	Update memory usage
				$memory_used+=$queue{$betoken}{"memreq"};
				#	Set flag
				$queue{$betoken}{"runed"} = 1;
				#	Set CPU to know which process hi douing
				$processor[$processor_free] = $betoken;
				#	Update CPU usage(size)
				$processors_used+=$queue{$betoken}{"procalloc"};
				#	Print needed informatio
				print "Run,\t" . $queue{$betoken}{'jobNumber'} . ",\t";
				print $sys_time . "\n";	
			}
			else
			{
				last;	#	Go next iteration
			}
		}
	}
}
###############################################################################
#	Function for updating wait time
sub UpdateWaitTime
{
	#	For each process waiting update wait time
	foreach $key(keys(%queue)) 
	{
		#	Check if process waiting
	  	if($queue{$key}{"runed"} == 0 )
	  	{
	  		$queue{$key}{"wait"}+=1;		#	Update
		}
  	}
}

###############################################################################
#	Function simulation work over some CPU wich is geted by parameter
#	and its id of CPU in array
sub CPUWork
{
	#	Decrease the runtime value for process
	$queue{$processor[$_[0]]}{"runtime"}--;
	
	#	Check if process end his job 
	if($queue{$processor[$_[0]]}{"runtime"} <= 0)
	{
		#	Free memory which this process used
		$memory_used-=$queue{$processor[$_[0]]}{"memreq"};
		#	Print the End message
		print "END ,\t" . $queue{$processor[$_[0]]}{"jobNumber"} . ",\t";
		print  $sys_time . "\n";
		
		#	Free CPU wich this process used
		$processors_used-=$queue{$processor[$_[0]]}{"procalloc"};
		#	Copy this process to hash of ended process 
		$completed{$processor[$_[0]]} = $queue{$processor[$_[0]]};
		#	Delete from queue
		delete $queue{$processor[$_[0]]};
		#	Clear CPU indicator to this process
		$processor[$_[0]] = '0';
	}
}

###############################################################################
#	Function wich do work for all CPU
#	Updating lab statistic variables
sub allProcWork
{
	#	Check if have used CPU if yes do next 
	if($processors_used != 0)
	{
		$proc_usage++;							#	Update statistic var
		$cpu_util+=$processors_used;			#	Update statistic var
		
		#	Do work for each CPU
		for($i=0;$i<$processors_size;$i++)
		{
			if($processor[$i] ne '0')
			{
				CPUWork($i);					#	DO Spec CPU work
			}
		}
	}
	
}

###############################################################################
my 	$process_counter	=	0;		#	Number process loaded to queue
my	$simulator_status 	= 	1;		#	Bool for when simulation have job to do
my 	$next_value 		= 	0;		#	Axelerator variable

#	Start do main loop of simulator of computer work
while($simulator_status)
{
		#sort {$HoH{$a}{"submit"} <=> $HoH{$b}{"submit"}} 
	
	#	Axelerator condition
	if($next_value == $sys_time)
	{
		foreach $key ((keys(%HoH))) 
		{
			#	Axeleration block. Used only for do fast results in program
			#	and not spell to much time for runing 1000(example) process
			#	Just calculate next time in which need add to queue 
			#	next process
			if($HoH{$key}{"submit"} > $sys_time)
			{
				if($next_value <= $sys_time){
					#	Update next operation value
					$next_value = $HoH{$key}{"submit"};
				}
				elsif($HoH{$key}{"submit"} < $next_value){
					#	Set minimal 
					$next_value = $HoH{$key}{"submit"};
				}
			}
			
			#	Check if have enough CPU only first iteration
			if($sys_time == 0 && $HoH{$key}{"procalloc"} > $processors_size)
			{
				print "Not enough processors!\n";
				print "Need >=".$HoH{$key}{"procalloc"}. "\n";
				exit;
			}
			
			#	Process from input hash going be loaded into queue
		  	if($HoH{$key}{"submit"} <= $sys_time)
		  	{
		  		$process_counter++;				#	Incarease statistic var
				PutProcessReadyToQueue($key);	#	Put int queue
				delete $HoH{$key};				#	Decrease hash
			}
	  	}		
	}
	
	#	Do computer simulation
	LoadFromQueueToProcessor();		#	Try to load from queue
	allProcWork();					#	Run CPU`s
	UpdateWaitTime();				#	Update waiting time
	
	#	Get size of hash tables
	$queue_size 		= 	keys(%queue);		#	Queue size
	$future_jobs_size 	= 	keys(%HoH);			#	Input size
	
	if($queue_size == 0 && $future_jobs_size){
		$sys_time+=$next_value-$sys_time;			#	Axeleration
	}
	elsif($queue_size == 0 && $future_jobs_size == 0){
		$simulator_status = 0;						#	Exit from loop
	}
	else{		
		$sys_time++;								#	simple mode
	}
}
###############################################################################
###############################################################################
	$wait_time = 0;
	foreach $key ((keys(%completed))) 
	{

	  	$wait_time+=$completed{$key}{"wait"} ;
	  	
  	}
###############################################################################
###############################################################################
	print "CPU usage $proc_usage \n";
	print "CPU util $cpu_util \n";
	
	$formula = ($proc_usage *$processors_size )/($cpu_util * $sys_time);
	print "The formula result is $formula \n";
	print "Wait time is : ". $wait_time/$process_counter ." \n";

###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
###############################################################################
#		UDALIT PERED SDACHEY
foreach $key (sort {$HoH{$a}{"submit"} <=> $HoH{$b}{"submit"}} (keys(%HoH))) 
{
  	if($HoH{$key}{"runtime"}>0 )
  	{
		print "Bad - Если бачишь цю хуйню - значит нехуя ты не ебу... \n";	
		last;
	}
}
