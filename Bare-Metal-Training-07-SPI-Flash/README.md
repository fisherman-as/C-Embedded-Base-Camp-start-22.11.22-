Assignment:
Need to open and rewrite “Time Capsule” based on 16 Mbit SPI Serial Flash memory (SPI Clock Frequency is 500kBit/s).
Read time capsule content and save it to the text file. If it is empty – inform your mentor about it.
Send email message to person who create it (with content attached). Put current mentor and previous person mentor as CC. “We found your time capsule…”.
Erase time capsule (all memory).
Write your own time capsule. Send a message with the contest to your current mentor.
Read it back from the memory to check that everything is fine (after the power cycle off/on).
Time capsule message
“From: @USERNAME, @EMAIL”
“Mentor: @USERNAME, @EMAIL”
“Date: @DATE”
“TIME CAPSULE”
Poetry / Lyrics here, favorite song, etc. (8 – 16 lines). See sample below.
Each line should be written to the start of new 4kB block of memory.
Each line should end with CR (\n = #13) symbol.
So 20 lines – 20 memory blocks used (from the beginning of memory).
Need to capture signal trace from for outputs with help of signal analyzer to show that all functionality is working fine.


Solution:



The following text was read from the flash:

From: Yaroslav Fur, yarosav.fur.w3@gmail.com
Mentor: Vitalii Kostiuk, vitalii.kostiuk@globallogic.com
Date: 25.11.2021
TIME CAPSULE
The following SCP object is a Beta-Gimmel-White level memetic hazard
that cannot be countered by current Foundation technology. Unauthorized
personnel viewing this file will be terminated. Authorized personnel
who do not wish to view this file should shut down their systems at this
time and submit to a superior for amnestic administration
LEVEL 5 AUTHORIZATION REQUIRED
REQUEST DENIED
Secure, Contain, Protect


The following text was written into the flash:

"From: Aleksey Yabanzhi, fisherman-as@ukr.net\n
Mentor: Artem Dovhal, artem.dovhal@globallogic.com\n
Date: 20.03.2023\n
TIME CAPSULE\n
To be or not to be - Shakespeare\n
The greatest glory in living lies not in never falling, \n
but in rising every time we fall. -Nelson Mandela\n
The way to get started is to quit talking and begin doing. -Walt Disney\n
Your time is limited, so don't waste it living someone else's life. \n
Don't be trapped by dogma, which is living with the results of other people's thinking. -Steve Jobs\n
If life were predictable it would cease to be life, and be without flavor. -Eleanor Roosevelt\n
If you look at what you have in life, you'll always have more. \n
If you look at what you don't have in life, you'll never have enough. -Oprah Winfrey\n
If you set your goals ridiculously high and it's a failure, \n
you will fail above everyone else's success. -James Cameron\n
Life is what happens when you're busy making other plans. -John Lennon\n
So, if you have read this text to this point, you can view my thoughts here.\n
I think we'll prevail. Hope it happens until 13.08.2023. However the more real date is \n
the summer of 2025's. If I'm not in the army yet, you can write me a mail:).\n
I like this courses, they gave me some practice and experience.\n";



The oscillogram is in Training07.sai