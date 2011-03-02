use LWP::Simple;

$url = get 'http://rutracker.org/forum/viewtopic.php?t=' . $ARGV[0] ; #3428704
#print $url;
if($url =~ m/(\<td class=\"message td2\" rowspan=\"2\"\>)(.{1,200})(.*)/i)
{
	print $1 . "\n";
	print $2 . "\n";	
	print $3 . "\n";
}