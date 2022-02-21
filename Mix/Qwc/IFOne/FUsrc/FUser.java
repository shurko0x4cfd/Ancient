/**
 * Created by Shurko on 19.04.2016. Public domain.
 */

class FUser {

	public static void main(String[] args)
    {
	Qwcdll.qwc();
    }

	public static void api_proc_1()
    {
        System.out.printf( "\n" );
        System.out.printf( "                 This message printed by \"Engine API\" function\n" );
        System.out.printf( "                   called from Forth via ENG-API-PROC-1 word." );
        System.out.printf( "\n" );
    }

static
	{
		System.loadLibrary("Qwcdll");
	}

}
