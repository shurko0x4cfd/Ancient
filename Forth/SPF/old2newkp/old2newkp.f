
\    "old2newkm 1.01 beta" Converter from old to new ".kp" format.
\    Copyright (c) 2013 Stadnichenko Alexandr.
\
\    This program is free software: you can redistribute it and/or modify
\    it under the terms of the GNU General Public License as published by
\    the Free Software Foundation, either version 3 of the License, or
\    (at your option) any later version.
\
\    This program is distributed in the hope that it will be useful,
\    but WITHOUT ANY WARRANTY; without even the implied warranty of
\    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
\    GNU General Public License for more details.
\
\    You should have received a copy of the GNU General Public License
\    along with this program.  If not, see <http://www.gnu.org/licenses/>.




\ =============================================================================
\ =                                Arrays                                     =
\ =============================================================================


: ARR
	CREATE	ALLOT
; \ end ARR




1024	ARR	CMDLN-OPTION-STR
1024	ARR	DIRPATH-STR
1024	ARR	COLORMAP
1024	ARR	READED-LINE



\ =============================================================================
\ =                    Variables, constant and values                         =
\ =============================================================================


\	String pointers and lenghts.

0	VALUE	CL-OPT-STRLEN
0	VALUE	DIRPATH-LEN
0	VALUE	ADDR-AFTER-BL-ERASE

\	File handlers.

0	VALUE	OLD-KP-FILE-HANDLER
0	VALUE	NEW.KP-FILE-HANDLER

\	Flags.

0	VALUE	IS-FILE-FLAG

\	Numbers and counters.

0	VALUE	TILES-COUNTER
0	VALUE	TILES-NUMBER
0	VALUE	PLOTS-NUMBER

\	Othes.

	VARIABLE	TEMP




\ =============================================================================
\ =                              Definitions                                  =
\ =============================================================================


: PRINT-LOGO

CR ."  _____________________________________________________________________________ "
CR ." |                                                                             |"
CR ." |        'old2newkm 1.01 beta' Converter from old to new '.kp' format.        |"
CR ." |                                                                             |"
CR ." |     Copyright (c) 2013 Stadnichenko Alexandr. Licension type: GNU GPL.      |"
CR ." |                                                                             |"
CR ." |       This program is distributed in the hope that it will be useful,       |"
CR ." |       but WITHOUT ANY WARRANTY; without even the implied warranty of        |"
CR ." |       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         |"
CR ." |       GNU General Public License for more details.                          |"
CR ." |                                                                             |"
CR ." |   Autors page: https://www.facebook.com/pages/KKnD-xDream/258660830915124   |"
CR ." |                                                                             |"
CR ." |                          Created width SP-FORTH 4.0                         |"
CR ." |                                                                             |"
CR ." |     I grateful Happiness for the new KKnD map editor and Andrew Cherezov    |"
CR ." |      and other developers for the forth-system programming SP-Forth 4.0.    |"
CR ." |                                                                             |"
CR ." |                          Last update : 19.02.2013                           |"
CR ." |_____________________________________________________________________________|"

; \ end PRINT-LOGO




: ERASE-BL-HEAD	( addr1 u1 -- addr2 u2 )

	DUP	0<>	( c-addr u 0|1 )

	BEGIN
	WHILE				( a1 u )
		SWAP	DUP	C@	( u  a1 char )
		0x21	<		( u  a1 0|-1 )
		SWAP	1+	SWAP	( u  a1 0|-1 )
		ROT			( a1 0|-1 u )
		1-	DUP	0<>	( a1 0|-1 u 0|-1 )
		ROT	AND	 	( a1 u 0|-1 )
	REPEAT

	1+	SWAP
	1-	SWAP

; \ end  ERASE-BL-HEAD




: PARSE-"..\DIRPATH\"			( fullpath-addres u1 -- u2 )

	ERASE-BL-HEAD
	-TRAILING

	OVER	+			( addr1 addr2 )

	BEGIN
		1-			( addr1 next-addr2)
		2DUP			( a1 a2 a1 a2 )
		=			( a1 a2 flag1 )
		OVER			( a1 a2 f1 a2 )
		C@	0x5C	=	( a1 a2 f1 f2 )
		OR			( a1 a2 f3 )
	UNTIL

	DUP	C@	0x5C	=
	IF
		SWAP	-	1+
	ELSE
		2DROP	0
	THEN

; \ end PARSE-"..\DIRPATH\"




: GET-CMDLN-OPT

	COMMANDLINE-OPTIONS
	ERASE-BL-HEAD	-TRAILING
	2DUP

	DUP
	IF
		DUP	TO	CL-OPT-STRLEN
		CMDLN-OPTION-STR	SWAP
		MOVE

		CMDLN-OPTION-STR	DIRPATH-STR	CL-OPT-STRLEN
		MOVE
	ELSE
		DROP	DROP
		CR	CR	." Not path in command line."

		CR	CR	." Press any key to exit."
		CR	KEY	DROP	BYE
	THEN

; \ end GET-CMDLN-OPT





: BYE-IF-PATH-DON'T-EXIST

	CMDLN-OPTION-STR	FALSE	FILE-EXIST	\ File exist?

	0=	IF
			CR	CR	." This file or path don't exist."

			CR	CR	." Press any key to exit."
			CR	KEY	DROP	BYE
		THEN

; \ end BYE-IF-PATH-DON'T-EXIST




: IS-FILE-OR-DIR?

	CMDLN-OPTION-STR	2+	CL-OPT-STRLEN	FILE-EXISTS	\ Is not directory?
	TO	IS-FILE-FLAG

; \ end IS-FILE-OR-DIR?




: CLOSE-NEW.KP-FILE

	NEW.KP-FILE-HANDLER	CLOSE-FILE	DROP

; \ end CLOSE-NEW.KP-FILE




: OPEN-OLD-KP-FILE

\	CMDLN-OPTION-STR	CL-OPT-STRLEN	CR	CR	TYPE

	CMDLN-OPTION-STR	CL-OPT-STRLEN	R/O	OPEN-FILE
		IF
			S" OPEN-OLD-KP-FILE: Unable to open .kp file."	CR	CR	TYPE
			CLOSE-NEW.KP-FILE

			CR	CR	." Press any key to exit."
			CR	KEY	DROP	BYE
		THEN

	TO	OLD-KP-FILE-HANDLER

; \ end OPEN-OLD-KP-FILE




: CLOSE-OLD-KP-FILE

	OLD-KP-FILE-HANDLER	CLOSE-FILE	DROP

; \ end CLOSE-OLD-KP-FILE




: CLOSE-ALL-FILES

	CLOSE-OLD-KP-FILE
	CLOSE-NEW.KP-FILE

; \ end CLOSE-ALL-FILES




: CREATE-NEW.KP-FILE

	DIRPATH-STR

	S" new.kp"	TUCK
	DIRPATH-STR	DIRPATH-LEN	+	SWAP	MOVE
	DIRPATH-STR	DIRPATH-LEN	+	+	0	SWAP	!
	FALSE

	W/O	CREATE-FILE
	0<>	IF
			CR	CR	." CREATE-NEW.KP-FILE: Unable to create 'new.kp' file."

			CR	CR	." Press any key to exit."
			CR	KEY	DROP	BYE
		THEN
	TO	NEW.KP-FILE-HANDLER

; \ end CREATE-NEW.KP-FILE




: BYE-BECAUSE-THIS-IS-NOT-FILE

	CR	CR	." This is not file."

	CR	CR	." Press any key to exit."
	CR	KEY	DROP	BYE

; \ end BYE-BECAUSE-THIS-IS-NOT-FILE




: BYE-IF-THIS-IS-NOT-FILE

	IS-FILE-FLAG	0=	IF
					BYE-BECAUSE-THIS-IS-NOT-FILE
				THEN	

; \ end	BYE-IF-THIS-IS-NOT-FILE




: BYE-IF-OLD-KP-FILE-TOO-SMALL		( ud_filesize -- )

	0x69	1024	+	0
	D<	IF
			CR	CR	." GET-FIRST-COLORMAP: .kp file too small."
			CLOSE-ALL-FILES

			CR	CR	." Press any key to exit."
			CR	KEY	DROP	BYE
		THEN

; \ end BYE-IF-OLD-KP-FILE-TOO-SMALL




: MSG-IF-IOR<>0

	?DUP
	IF
		." MSG-IF-IOR<>0: Diagnostic message: READ-FILE returned ior: "
		. ." ."
	THEN

; \ end MSG-IF-IOR<>0




: SKIP-PATH-STRING

	READED-LINE	5	OLD-KP-FILE-HANDLER	READ-FILE
	MSG-IF-IOR<>0	DROP

	READED-LINE	DUP
	4	+	C@
	OLD-KP-FILE-HANDLER	READ-FILE	\ Skip path sting.
	MSG-IF-IOR<>0	DROP

; \ end SKIP-PATH-STRING




: FILE-SKIP-N		( u -- )

	READED-LINE	SWAP	OLD-KP-FILE-HANDLER	READ-FILE
	MSG-IF-IOR<>0	DROP

; \ end FILE-SKIP-N




: READ-TILES-NUMBER

	READED-LINE	2	OLD-KP-FILE-HANDLER	READ-FILE
	MSG-IF-IOR<>0	DROP

	READED-LINE	DUP	C@	SWAP	1+	C@	0x100	*	+
	TO	TILES-NUMBER

; \ end READ-TILES-NUMBER




: READ-PLOTS-NUMBER

	READED-LINE	2	OLD-KP-FILE-HANDLER	READ-FILE
	MSG-IF-IOR<>0	DROP

	READED-LINE	DUP	C@	SWAP	1+	C@	0x100	*	+
	TO	PLOTS-NUMBER

; \ end READ-PLOTS-NUMBER




: BYE-IF-NOT-8-BPP

	READED-LINE	28	OLD-KP-FILE-HANDLER	READ-FILE
	MSG-IF-IOR<>0	DROP

	READED-LINE	4	OLD-KP-FILE-HANDLER	READ-FILE
	MSG-IF-IOR<>0	DROP

	READED-LINE	@	8
	<>	IF
			CR	CR	." BYE-IF-NOT-8-BPP: KP file must not contain non 8 bit per pixel images."
			CLOSE-ALL-FILES

			CR	CR	." Press any key to exit."
			CR	KEY	DROP	BYE
		THEN

; \ end BYE-IF-NOT-8-BPP




: BYE-IF-NOT-ALL-256-COLOR-PRESENT

	READED-LINE	14	OLD-KP-FILE-HANDLER	READ-FILE
	MSG-IF-IOR<>0	DROP

	READED-LINE	4	OLD-KP-FILE-HANDLER	READ-FILE
	MSG-IF-IOR<>0	DROP

	READED-LINE	@	DUP	0<>	SWAP	0x100	<>	AND
	IF
		CR	CR	." BYE-IF-NOT-ALL-256-COLOR-PRESENT: Colormap must contain all 256 colors."
		CLOSE-ALL-FILES

		CR	CR	." Press any key to exit."
		CR	KEY	DROP	BYE
	THEN

; \ end  BYE-IF-NOT-ALL-256-COLOR-PRESENT




: STORE-COLORMAP

	READED-LINE	1024	OLD-KP-FILE-HANDLER	READ-FILE
	MSG-IF-IOR<>0	DROP

	READED-LINE	COLORMAP	1024	MOVE

; \ end STORE-COLORMAP




: GET-FIRST-COLORMAP	\	0x69

	OLD-KP-FILE-HANDLER	FILE-SIZE
	MSG-IF-IOR<>0
	BYE-IF-OLD-KP-FILE-TOO-SMALL

	SKIP-PATH-STRING
	READ-TILES-NUMBER
	BYE-IF-NOT-8-BPP
	BYE-IF-NOT-ALL-256-COLOR-PRESENT
	4	FILE-SKIP-N
	STORE-COLORMAP

\	KEY	DROP	CLOSE-ALL-FILES		BYE

; \ end GET-FIRST-COLORMAP




: GET-PLOTS-NUMBER

	TILES-NUMBER	TO	TILES-COUNTER
	1024	FILE-SKIP-N			\	Skip first tilebody.

	BEGIN
		TILES-COUNTER	1-	DUP	TO	TILES-COUNTER
	WHILE
		BYE-IF-NOT-8-BPP
		BYE-IF-NOT-ALL-256-COLOR-PRESENT
		4	FILE-SKIP-N
		1024	FILE-SKIP-N
		1024	FILE-SKIP-N
	REPEAT

	READ-PLOTS-NUMBER

; \ end GET-PLOTS-NUMBER




: REOPEN-OLD-KP

	CLOSE-OLD-KP-FILE
	OPEN-OLD-KP-FILE

; \ end  REOPEN-OLD-KP




: PROCESS-OLD-KP

	S" KTP0"	NEW.KP-FILE-HANDLER	WRITE-FILE	DROP

	0x0	TEMP	!
	TEMP	4	NEW.KP-FILE-HANDLER	WRITE-FILE	DROP

	TILES-NUMBER	TEMP	!
	TEMP	4	NEW.KP-FILE-HANDLER	WRITE-FILE	DROP

	PLOTS-NUMBER	TEMP	!
	TEMP	4	NEW.KP-FILE-HANDLER	WRITE-FILE	DROP

	S" BMIF"	NEW.KP-FILE-HANDLER	WRITE-FILE	DROP

	0x28	TEMP	!
	TEMP	4	NEW.KP-FILE-HANDLER	WRITE-FILE	DROP

	0x20	TEMP	!
	TEMP	4	NEW.KP-FILE-HANDLER	WRITE-FILE	DROP

	0x20	TEMP	!
	TEMP	4	NEW.KP-FILE-HANDLER	WRITE-FILE	DROP

	0x080001	TEMP	!
	TEMP	4	NEW.KP-FILE-HANDLER	WRITE-FILE	DROP	

	0x0	TEMP	!
	TEMP	4	NEW.KP-FILE-HANDLER	WRITE-FILE	DROP

	0x0	TEMP	!
	TEMP	4	NEW.KP-FILE-HANDLER	WRITE-FILE	DROP

	0x0	TEMP	!
	TEMP	4	NEW.KP-FILE-HANDLER	WRITE-FILE	DROP

	0x0	TEMP	!
	TEMP	4	NEW.KP-FILE-HANDLER	WRITE-FILE	DROP

	0x0100	TEMP	!
	TEMP	4	NEW.KP-FILE-HANDLER	WRITE-FILE	DROP

	0x0	TEMP	!
	TEMP	4	NEW.KP-FILE-HANDLER	WRITE-FILE	DROP

	COLORMAP	1024
			NEW.KP-FILE-HANDLER	WRITE-FILE	DROP

	S" BITS"	NEW.KP-FILE-HANDLER	WRITE-FILE	DROP


	TILES-NUMBER	TO	TILES-COUNTER
	SKIP-PATH-STRING
	2	FILE-SKIP-N

	BEGIN
		TILES-COUNTER
	WHILE
		54	FILE-SKIP-N
		1024	FILE-SKIP-N

		READED-LINE	1024	OLD-KP-FILE-HANDLER	READ-FILE
		MSG-IF-IOR<>0	DROP
		READED-LINE	1024	NEW.KP-FILE-HANDLER	WRITE-FILE	DROP

		TILES-COUNTER	1-	TO	TILES-COUNTER
	REPEAT

	2	FILE-SKIP-N

	BEGIN
		READED-LINE	1024	OLD-KP-FILE-HANDLER	READ-FILE
		MSG-IF-IOR<>0
		?DUP
	WHILE
		READED-LINE	SWAP	NEW.KP-FILE-HANDLER	WRITE-FILE	DROP
	REPEAT

; \ end PROCESS-OLD-KP




\ =============================================================================
\ =                            Main definition                                =
\ =============================================================================


: OLD-KP-TO-NEW-KP

	PRINT-LOGO

	GET-CMDLN-OPT
	BYE-IF-PATH-DON'T-EXIST

	IS-FILE-OR-DIR?
	BYE-IF-THIS-IS-NOT-FILE

	DIRPATH-STR	CL-OPT-STRLEN	PARSE-"..\DIRPATH\"
	TO	DIRPATH-LEN

	CREATE-NEW.KP-FILE
	OPEN-OLD-KP-FILE

	GET-FIRST-COLORMAP
	GET-PLOTS-NUMBER

	REOPEN-OLD-KP

	PROCESS-OLD-KP


	CLOSE-ALL-FILES

	CR	CR	." Process successfully completed. Press any key to exit."
	CR	KEY	DROP	BYE

; \ end OLD-KP-TO-NEW-KP




\ =============================================================================
\ =                                 Build                                     =
\ =============================================================================


0	TO	SPF-INIT?
'	OLD-KP-TO-NEW-KP	TO	<MAIN>
S" C:\Root\Data\Creation\Coding\Forth\spf40\old2newkp\old2newkp.exe"	SAVE




























