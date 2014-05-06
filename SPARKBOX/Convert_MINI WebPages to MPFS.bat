del MPFSImg2.c

mkdir WebPages2_mini
copy WebPages2\*.xml WebPages2_mini\*.xml
copy WebPages2\*.jpg WebPages2_mini\*.jpg
copy WebPages2\*.png WebPages2_mini\*.png
copy WebPages2\*.cgi WebPages2_mini\*.cgi
copy WebPages2\*.csv WebPages2_mini\*.csv

java -jar htmlcompressor-1.5.3.jar  --charset windows-1250 -o WebPages2_mini\ WebPages2\*.inc
java -jar htmlcompressor-1.5.3.jar  --charset windows-1250 -o WebPages2_mini\ WebPages2\*.htm
java -jar yuicompressor-2.4.7.jar --nomunge WebPages2\sparkbox.css -o WebPages2_mini\sparkbox.css
java -jar yuicompressor-2.4.7.jar  --nomunge WebPages2\sparkbox.js -o WebPages2_mini\sparkbox.js 

"..\Microchip\TCPIP Stack\Utilities\MPFS2.jar" /mpfs2 /html "*.htm, *.html, *.cgi, *.xml, *.log, *.csv" /C18_C32  ".\WebPages2_mini" "." "MPFSImg2.c"
rmdir WebPages2_mini /Q /S
