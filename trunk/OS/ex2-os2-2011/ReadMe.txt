	EX2	::	Parser of c-file for puting comments
===============================================================================
Authors:
	Andrey Shamis,  	id: 321470882, login: andreysh
	Ilia Gaisinsky, 	id: 309480051, login: iliaga
=============================================================================== 
	for run the script
		my_doc.pl <input_file_name>
	
	for set executable
		chmod +x my_doc.pl

	Files be created after runing 
		# my_doc.pl <input_file_name>
				-	<input_file_name>.doc.c
				-	<input_file_name>.pdf
	The files be created only if input file not include any comments in code!


===============================================================================
Using Pdf creator
  INSTALLATION OF PDF CREATOR

    Quick answer:

        perl -MCPAN -e 'install PDF::Create'

    Long answer:

    To install manually, cd to the directory containing the unpacked
    distribution and do one of the following:

    a.  Create a makefile by running Makefile.PL using the perl
        program into whose library you want to install and then run
        make three times:

            perl Makefile.PL
            make
            make test
            make install

    b.  To install into a private library, for example your home
        directory:

            perl Makefile.PL INSTALLSITELIB=$HOME/lib INSTALLMAN3DIR=$HOME/man
            make
            make test
            make pure_install