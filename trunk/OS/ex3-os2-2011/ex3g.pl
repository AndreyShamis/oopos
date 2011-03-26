#!/usr/bin/perl -w

use LWP::Simple;
use IO::Zlib;

use Data::Dump qw(dump);

$fh = new IO::Zlib;

#$url = get 'http://www.cs.huji.ac.il/labs/parallel/workload/l_das2/DAS2-fs1-2003-1.swf.gz';


my $counter = 0;
my %HoH = () ;

if ($fh->open("DAS2-fs1-2003-1.swf.gz", "r")) 
{
	@data = <$fh>;
	
	foreach $line(@data)
	{
		if(substr($line,0,1) ne ';' && $counter == 0)
		{
			$counter = 1;
		}

		if($counter>0)
		{
			$string =  $line;
			$string =~ s/^\s+//; 
			
			my (
					$jobNumber, 
					$Submit, 
					$wait,
					$runtime, 
					$procalloc, 
					$cpuused, 
					$memused,
					$procreq,
					$userest,
					$memreq,
					$status,
					$uid,
					$gid,
					$exenum,
					$qnum,
					$partition,
					$prevjob,
					$thinktime
				)
				=	split(/\s+/,$string);
			$counter++;
			$HoH{$jobNumber} = 
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

		if($counter > 20)
		{
			last;
		}
	}
	$fh->close;
}
	
	
	
	print dump(%HoH);

