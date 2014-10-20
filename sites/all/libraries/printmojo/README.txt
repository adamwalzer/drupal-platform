Printmojo.com Store Syndication
*******************************
Updated   : December 17, 2007

This package contains a script and accompanying files which enable an
existing web site to 'syndicate' a printmojo.com Store, that is, to
display products, and allow adding items to a printmojo.com shopping
basket.

Requirements
------------
  PHP 4+
  A PrintMojo.com Merchant Account with products available for sale
  3 minutes in which to install the script!

Installation
------------
WE ALSO HAVE A QUICK VIDEO TUTORIAL TO WALK YOU THROUGH THE INSTALLATION PROCESS ON
THE SAME PAGE WHERE YOU DOWNLOADED THIS SCRIPT. JUST LOGIN TO YOUR PRINTMOJO ACCOUNT TO VIEW IT

  1. Open the file mojostore.php in a text editor (for example, notepad).

  2. Edit the configuration values for the Store Name, your username,
       password and the url at which you will upload mojostore.php. Optionally, you can
     set the CACHE type to speed up the loading of the script.

NOTE: BE SURE TO EDIT THE PART AFTER THE EQUALS = SIGN AND IN BETWEEN THE SINGLE QUOTES ''

  a) The 'StoreName' can be found by logging into your PrintMojo account.

  b) Once logged in, look at the URL in your browser's address bar:
   (ex: http://www.printmojo.com/Manage/YourStore/index.php)

  c) Your storename is the part after /Manage/ and before /index.php

  3. Open the file pm_layout.html in your favorite HTML editor.

  4. Edit the html in any way you desire, placing the special code
       {body} in the location where you wish the products, basket etc
       to display.

  5. Upload all the files to your webserver.

  6. If you get an error that says something like:

"Unable to access your store data, check username and password. ../.../mojostore.php line 668"
     
     You will need to use the mojostore_CURL.php version of the script. Rename this file mojostore.php and 
     follow steps 1, 2 and 5 above.


Usage
-----
  After you have uploaded the files to your webserver you will be able
  to access the following URL's (replace www.example.com of course!)

  http://www.example.com/mojostore.php?_=list_categories
  http://www.example.com/mojostore.php?_=list

Customisation
-------------
  There are two levels of customisation available to you.  Always make a
  backup of any files before editing them!

  Layout Customisation
  ....................
  To customise the overall layout of the pages, edit the plain HTML file
  'pm_layout.html'.  This is standard HTML (with CSS, Javascript, whatever
  you like), and includes one special code, '{body}', which you must place
  where you would like the page content to appear.

  Content Customisation
  .....................
  The content of each page (for example the 'shopping basket') is also
  customisable, these are called 'templates'.  You must edit these inside
  the mojostore.php file, where you will find directions relating to the
  editing of the available templates.

