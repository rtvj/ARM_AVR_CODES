#include<stdio.h>
main( )
{
	FILE *fs,*ft;
	char ch;
	
	char source[10],target[10];
/*
	puts("enter source file name :\n");
	gets(source);

	puts("enter target file name :\n");
	gets(target);
	*/
	fs = fopen("./a.txt","w");

	if ( fs == NULL )
	{
		printf( "Cannot open source file\n" );
	}
	else
	{
		printf("successfully opened source file\n");
	}

	filecopy("nikhil",fs);
	
	//fclose(fs);


	ft = fopen ("./b.txt","w");
	if ( ft == NULL )
	{
	printf( "Cannot open target file\n" ) ;
	//fclose (fs);
	}
	else
	{
		printf("successfully opened target file\n");
	}
	printf( "files copied\n" );
	filecopy(fs,ft);
	fclose(ft);
}

 
 filecopy( char *t, char *s )
{
	while ( *s != '\0' )
	{
	*t = *s ;
	s++ ;
	t++ ;
	}
	*t = '\0' ;
}

