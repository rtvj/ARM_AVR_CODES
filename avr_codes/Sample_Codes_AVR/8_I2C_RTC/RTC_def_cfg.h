#ifndef _RTC_def
#define _RTC_def
	#define SLAVE_ADDRESS 	0xD0
	#define WORD_ADDRESS	0x00
	#define SECONDS			0x41
	#define MINUTES			0x59
	#define HOURS			0x11
	#define DAY_OF_WEEK		0x1
	#define DATE			0x10
	#define MONTH			0x1
	#define YEAR			0x09
	
	
	/*********** use if you want 12 hrs mode *****************/
	/* uncomment the below statement if you want 12 hrs mode */

	/* #define _12_HRS_MODE_ON */


	/************* CAUTION DONOT MODIFY THIS ***************/
	#ifdef _12_HRS_MODE_ON
		#define PM 1
		#define	AM 0
	#endif
	/*****************************************************/

	/* set AM or PM here */

	#ifdef _12_HRS_MODE_ON
		#define HRS_AM_PM	PM
	#endif


	#ifdef	_12_HRS_MODE_ON
		#if HRS_AM_PM /* IF PM  */
			#define _HOURS		HOURS | (1<<6) | (1<<5)
		#else		 /*	ELSE AM */
			#define _HOURS		HOURS | (1<<6) & ~(1<<5)
		#endif
	#else
		#define _HOURS			HOURS & ~(1<<6)
	#endif

#endif
