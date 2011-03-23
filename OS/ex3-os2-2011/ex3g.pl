#!/usr/bin/perl -w

use LWP::Simple;
use IO::Zlib;
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
			#print $line;
			my ($jobNumber, $Submit, $wait, $runtime, $proc_alloc, $cpu_used, $mem_used
			,$proc_req,$user_est,$mem_req,$status,$uid,$gid,$exe_num,$q_num,$partition,$prev_job,$think_time)=split(/\t/,$line);
			$counter++;
			$HoH{$jobNumber}{'jobNumber'} 	= $jobNumber;
			$HoH{$jobNumber}{'Submit'} 		= $Submit;
			$HoH{$jobNumber}{'Wait'} 		= $wait;
			$HoH{$jobNumber}{'Runtime'} 	= $runtime;
		}

		if($counter > 20)
		{
			last;
		}
	}
	$fh->close;
}


foreach $key (sort keys %HoH) {
    
    print "$key";
}
	
#print $url;