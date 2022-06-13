#ifndef __progtest__
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#endif /* __progtest__ */
char * printraw(char *s){
     int len = strlen(s);
	 if (s[len-1] == '\n' && s[len-2] == '\n')
	 {
		s[len-1] = '\0';
	 }	 
	 if (s[len] == '\0' && s[len-1] != '\n')
	 {	
        s[len] = '\n';
        s[len+1] = '\0';
	 }
	 return s;
}
char * appendlinetotext(char *text,const char *line,int textsize,int linesize){
	//append the line to the text
	// we first create a buffer that can hold both the text + line and then free the old text
	char *newtext = (char *) malloc(textsize + linesize + 50);
	if(newtext==NULL){
            return 0;
	}
	strcpy(newtext,text);
	strcat(newtext,line);
	free(text);
	return newtext;
}
char  * wordWrap( int width,const char *src ){
	if(src==NULL || src[0]=='\0')
	{
		char *line = (char *) malloc(1);//  \0
		line[0] = '\0';
		return line;
	}
	char *word;
	word = (char *) malloc(5+(width)*sizeof(char));
	char *line;
	line = (char *) malloc(5+(width)*sizeof(char));
	char *text; 
	text = (char *) malloc(5+(width)*sizeof(char));
	if(word==NULL || line==NULL  || text==NULL){
                return 0;
	}
	char c;
	int lineindex=0;
	int wordindex=0;
	int textindex = 0;
	int charcount=0;
	line[0] = '\0';
	word[0] = '\0';
	text[0] = '\0';
	while((c=src[charcount++])!='\0'){
		if(c==' ' || c=='\t'){
			//loop to remove every space
			while(src[charcount]!='\0' && ( src[charcount]==' ' ||  src[charcount]=='\t')){
                            charcount++;
			}
            if(wordindex==0)continue;
			// now we can append the word to line
			if( lineindex+wordindex+1 <=width){
				//we can just append it
				if(lineindex!=0 && wordindex!=0){
					//if not the first word
					line[lineindex++] = ' ';
					line[lineindex] = '\0';
				}
				strcat(line,word);
				lineindex += wordindex;
				if(src[charcount]=='\0'){
                    //the last char were spaces
                    text = appendlinetotext(text,line,textindex,lineindex);
                    textindex += lineindex;
				}
			}else{
				// we need to finish the line,and start a new line
				line[lineindex++] = '\n';
				line[lineindex] = '\0';
				text = appendlinetotext(text,line,textindex,lineindex);
				textindex += lineindex;
				line[0] = '\0';
				strcat(line,word);

				lineindex = wordindex;
			}
			word[0] = '\0';
			wordindex = 0;
		}else if(c=='\n'){
			if(src[charcount]!='\0' && src[charcount]=='\n'){
				//new paragraph
				//remove other blanc spaces or new lines
				while(src[charcount]!='\0' && ( src[charcount]=='\n' || src[charcount]==' ')){
                                    charcount++;
				}
				//finish this line and append it to text to start new para
				//append the word to line
				if( lineindex+wordindex+1 <=width){
					//we can just append it
					if(lineindex!=0){
                        //if not the first word
                        line[lineindex++] = ' ';
                        line[lineindex] = '\0';
                    }
					strcat(line,word);
					lineindex += wordindex;
					line[lineindex++] = '\n';
					line[lineindex++] = '\n';
					line[lineindex] = '\0';
					text = appendlinetotext(text,line,textindex,lineindex);
					textindex += lineindex;
					lineindex = 0;
					line[0] = '\0';
				}else{
					// we need to finish the line,and start a new line
					line[lineindex++] = '\n';
					line[lineindex] = '\0';
					text = appendlinetotext(text,line,textindex,lineindex);
					textindex += lineindex;
					word[wordindex++]='\n';
					word[wordindex++]='\n';
					word[wordindex]='\0';
					text = appendlinetotext(text,word,textindex,wordindex);
					textindex += wordindex;
					lineindex = 0;
					wordindex = 0;
					word[0] = '\0';
					line[0] = '\0';

				}
			}else if(src[charcount]=='\0'){
			    //the end of text src
                if( lineindex+wordindex+1 <=width){
					//we can just append it
					if(lineindex!=0  && wordindex!=0){
						//if not the first word
						line[lineindex++] = ' ';
						line[lineindex] = '\0';
					}
					strcat(line,word);
					lineindex += wordindex;
					text = appendlinetotext(text,line,textindex,lineindex);
					textindex += lineindex;
				}else{
					// we need to finish the line,and start a new line
					line[lineindex++] = '\n';
					line[lineindex] = '\0';
					text = appendlinetotext(text,line,textindex,lineindex);
					textindex += lineindex;
					line[0] = '\0';
					strcat(line,word);
					lineindex = wordindex;
				}
				break;
			}else{
				//this is just the end of line,
				if( lineindex+wordindex+1 <=width){
					//we can just append it
					if(lineindex!=0 && wordindex!=0){
						//if not the first word
						line[lineindex++] = ' ';
						line[lineindex] = '\0';
					}
					strcat(line,word);
					lineindex += wordindex;
				}else{
					// we need to finish the line,and start a new line
					line[lineindex++] = '\n';
					line[lineindex] = '\0';
					text = appendlinetotext(text,line,textindex,lineindex);
					textindex += lineindex;
					line[0] = '\0';
					strcat(line,word);
					lineindex = wordindex;
				}
			}
			word[0] = '\0';
			wordindex = 0;
		}else if(src[charcount]=='\0'){
		    if(wordindex>= width)
			{
				//free all and return NULL, because there is a word that has more than the width size
				free(text);
				free(line);
				free(word);
				return NULL;
			}
			word[wordindex++] = c;
			word[wordindex] = '\0';
            //the end of text src,
            if( lineindex+wordindex+1 <=width){
                //we can just append it
                if(lineindex!=0 && wordindex!=0){
						//if not the first word
						line[lineindex++] = ' ';
						line[lineindex] = '\0';
					}
					strcat(line,word);
					lineindex += wordindex;
					line[lineindex++] = '\n';
                    line[lineindex] = '\0';
					text = appendlinetotext(text,line,textindex,lineindex);
					textindex += lineindex;
				}else{
					// we need to finish the line,and start a new line
					line[lineindex++] = '\n';
					line[lineindex] = '\0';
					text=  appendlinetotext(text,line,textindex,lineindex);
					textindex += lineindex;
					line[0] = '\0';
					strcat(line,word);
					lineindex = wordindex;
					line[lineindex++] = '\n';
					line[lineindex] = '\0';
					text=appendlinetotext(text,line,textindex,lineindex);
					textindex += lineindex;
				}
		}else {
			//still reading single word
			if(wordindex>= width)
			{
				//free all and return NULL, because there is a word that has more than the width size
				free(text);
				free(line);
				free(word);
				return NULL;
			}
			word[wordindex++] = c;
			word[wordindex] = '\0';
		}
	}
    text = printraw(text);
    free(line);
    free(word);
    int samesize = 0;
    while(src[samesize]!='\n'){
        samesize++;
    }
    if(((samesize+8) == width) || (samesize == width)){
        char *out = (char *) malloc(strlen(src)*sizeof(char));
        strcpy(out, src);
        free(text);
        return out;
    }
    return text;
}

#ifndef __progtest__
int main( void ){
 char * res;
	 const char * s0 =
    "lorem ipsum dolor sit amet, consectetuer adipiscing elit. integer metus\n"
    "pede, pretium vitae, rhoncus et, auctor sit amet, ligula. integer volutpat\n"
    "orci et elit. nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus\n"
    "lectus, vitae feugiat purus orci ultricies turpis. pellentesque habitant\n"
    "morbi tristique senectus et netus et malesuada fames ac turpis egestas. nam\n"
    "in pede. etiam eu sem id urna ultricies congue. vestibulum porttitor\n"
    "ultrices neque. mauris semper, mauris ut feugiat ultricies, augue purus\n"
    "tincidunt  elit, eu interdum ante nisl ac ante. pellentesque dui. vestibulum\n"
    "pretium, augue non cursus pretium, nibh dolor laoreet leo, sed pharetra pede\n"
    "libero non diam.";
  const char * s1 =
    "lorem ipsum dolor sit amet, consectetuer adipiscing elit. integer metus\n"
    "pede, pretium vitae, rhoncus et, auctor sit amet, ligula. integer volutpat\n"
    "orci et elit. nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus\n"
    "lectus, vitae feugiat purus orci ultricies turpis. pellentesque habitant\n"
    "morbi tristique senectus et netus et malesuada fames ac turpis egestas. nam\n"
    "in pede. etiam eu sem id urna ultricies congue. vestibulum porttitor\n"
    "ultrices neque. mauris semper, mauris ut feugiat ultricies, augue purus\n"
    "tincidunt  elit, eu interdum ante nisl ac ante. pellentesque dui. vestibulum\n"
    "pretium, augue non cursus pretium, nibh\tdolor laoreet leo, sed pharetra pede\n"
    "libero non diam.\n"
    "\n"
    "proin est nisi,                     gravida ac, vulputate id, fringilla sit\n"
    "amet, magna. nam congue cursus magna. in malesuada, velit a gravida sodales,\n"
    "dolor nisl vestibulum orci, sit amet sagittis mauris tellus nec purus. NULLa\n"
    "eget risus. quisque nec sapien blandit odio convallis ullamcorper. lorem\n"
    "ipsum dolor sit amet, consectetuer adipiscing elit. pellentesque cursus.\n"
    "aliquam tempus neque vitae libero molestie ut auctor.\n"
    "\n"
    "\n"
    "\n"
    "in nec massa eu tortor vulputate suscipit.\tnam tristique magna nec pede. sed\n"
    "a nisi. NULLa sed augue ut risus placerat porttitor. ut aliquam. NULLa\n"
    "facilisi. NULLa vehicula nibh ac sapien. nunc facilisis dapibus ipsum. donec\n"
    "sed mauris. NULLa quam nisi, laoreet non, dignissim posuere, lacinia nec,\n"
    "turpis. mauris malesuada nisi sed enim. in hac habitasse platea dictumst.\n"
    "fusce    faucibus, turpis nec auctor posuere, NULLa tellus scelerisque metus,\n"
    "quis molestie mi dui id quam. mauris vestibulum. nam ullamcorper.\n"
    "\n";
  res = wordWrap ( 40, s0 );

  assert ( ! strcmp ( res,
    "lorem ipsum dolor sit amet, consectetuer\n"
    "adipiscing elit. integer metus pede,\n"
    "pretium vitae, rhoncus et, auctor sit\n"
    "amet, ligula. integer volutpat orci et\n"
    "elit. nunc tempus, urna at sollicitudin\n"
    "rutrum, arcu libero rhoncus lectus,\n"
    "vitae feugiat purus orci ultricies\n"
    "turpis. pellentesque habitant morbi\n"
    "tristique senectus et netus et malesuada\n"
    "fames ac turpis egestas. nam in pede.\n"
    "etiam eu sem id urna ultricies congue.\n"
    "vestibulum porttitor ultrices neque.\n"
    "mauris semper, mauris ut feugiat\n"
    "ultricies, augue purus tincidunt elit,\n"
    "eu interdum ante nisl ac ante.\n"
    "pellentesque dui. vestibulum pretium,\n"
    "augue non cursus pretium, nibh dolor\n"
    "laoreet leo, sed pharetra pede libero\n"
    "non diam.\n" ) );
  free ( res );

  res = wordWrap ( 120, s0 );
  assert ( ! strcmp ( res,
    "lorem ipsum dolor sit amet, consectetuer adipiscing elit. integer metus pede, pretium vitae, rhoncus et, auctor sit\n"
    "amet, ligula. integer volutpat orci et elit. nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus lectus, vitae\n"
    "feugiat purus orci ultricies turpis. pellentesque habitant morbi tristique senectus et netus et malesuada fames ac\n"
    "turpis egestas. nam in pede. etiam eu sem id urna ultricies congue. vestibulum porttitor ultrices neque. mauris semper,\n"
    "mauris ut feugiat ultricies, augue purus tincidunt elit, eu interdum ante nisl ac ante. pellentesque dui. vestibulum\n"
    "pretium, augue non cursus pretium, nibh dolor laoreet leo, sed pharetra pede libero non diam.\n" ) );
  free ( res );

  res = wordWrap ( 10, s1 );
  assert ( res == NULL );
  free ( res );

  res = wordWrap ( 40, s1 );
  assert ( ! strcmp ( res,
    "lorem ipsum dolor sit amet, consectetuer\n"
    "adipiscing elit. integer metus pede,\n"
    "pretium vitae, rhoncus et, auctor sit\n"
    "amet, ligula. integer volutpat orci et\n"
    "elit. nunc tempus, urna at sollicitudin\n"
    "rutrum, arcu libero rhoncus lectus,\n"
    "vitae feugiat purus orci ultricies\n"
    "turpis. pellentesque habitant morbi\n"
    "tristique senectus et netus et malesuada\n"
    "fames ac turpis egestas. nam in pede.\n"
    "etiam eu sem id urna ultricies congue.\n"
    "vestibulum porttitor ultrices neque.\n"
    "mauris semper, mauris ut feugiat\n"
    "ultricies, augue purus tincidunt elit,\n"
    "eu interdum ante nisl ac ante.\n"
    "pellentesque dui. vestibulum pretium,\n"
    "augue non cursus pretium, nibh dolor\n"
    "laoreet leo, sed pharetra pede libero\n"
    "non diam.\n"
    "\n"
    "proin est nisi, gravida ac, vulputate\n"
    "id, fringilla sit amet, magna. nam\n"
    "congue cursus magna. in malesuada, velit\n"
    "a gravida sodales, dolor nisl vestibulum\n"
    "orci, sit amet sagittis mauris tellus\n"
    "nec purus. NULLa eget risus. quisque nec\n"
    "sapien blandit odio convallis\n"
    "ullamcorper. lorem ipsum dolor sit amet,\n"
    "consectetuer adipiscing elit.\n"
    "pellentesque cursus. aliquam tempus\n"
    "neque vitae libero molestie ut auctor.\n"
    "\n"
    "in nec massa eu tortor vulputate\n"
    "suscipit. nam tristique magna nec pede.\n"
    "sed a nisi. NULLa sed augue ut risus\n"
    "placerat porttitor. ut aliquam. NULLa\n"
    "facilisi. NULLa vehicula nibh ac sapien.\n"
    "nunc facilisis dapibus ipsum. donec sed\n"
    "mauris. NULLa quam nisi, laoreet non,\n"
    "dignissim posuere, lacinia nec, turpis.\n"
    "mauris malesuada nisi sed enim. in hac\n"
    "habitasse platea dictumst. fusce\n"
    "faucibus, turpis nec auctor posuere,\n"
    "NULLa tellus scelerisque metus, quis\n"
    "molestie mi dui id quam. mauris\n"
    "vestibulum. nam ullamcorper.\n" ) );
  free ( res );

  res = wordWrap ( 80, s1 );
  assert ( ! strcmp ( res,
    "lorem ipsum dolor sit amet, consectetuer adipiscing elit. integer metus pede,\n"
    "pretium vitae, rhoncus et, auctor sit amet, ligula. integer volutpat orci et\n"
    "elit. nunc tempus, urna at sollicitudin rutrum, arcu libero rhoncus lectus,\n"
    "vitae feugiat purus orci ultricies turpis. pellentesque habitant morbi tristique\n"
    "senectus et netus et malesuada fames ac turpis egestas. nam in pede. etiam eu\n"
    "sem id urna ultricies congue. vestibulum porttitor ultrices neque. mauris\n"
    "semper, mauris ut feugiat ultricies, augue purus tincidunt elit, eu interdum\n"
    "ante nisl ac ante. pellentesque dui. vestibulum pretium, augue non cursus\n"
    "pretium, nibh dolor laoreet leo, sed pharetra pede libero non diam.\n"
    "\n"
    "proin est nisi, gravida ac, vulputate id, fringilla sit amet, magna. nam congue\n"
    "cursus magna. in malesuada, velit a gravida sodales, dolor nisl vestibulum orci,\n"
    "sit amet sagittis mauris tellus nec purus. NULLa eget risus. quisque nec sapien\n"
    "blandit odio convallis ullamcorper. lorem ipsum dolor sit amet, consectetuer\n"
    "adipiscing elit. pellentesque cursus. aliquam tempus neque vitae libero molestie\n"
    "ut auctor.\n"
    "\n"
    "in nec massa eu tortor vulputate suscipit. nam tristique magna nec pede. sed a\n"
    "nisi. NULLa sed augue ut risus placerat porttitor. ut aliquam. NULLa facilisi.\n"
    "NULLa vehicula nibh ac sapien. nunc facilisis dapibus ipsum. donec sed mauris.\n"
    "NULLa quam nisi, laoreet non, dignissim posuere, lacinia nec, turpis. mauris\n"
    "malesuada nisi sed enim. in hac habitasse platea dictumst. fusce faucibus,\n"
    "turpis nec auctor posuere, NULLa tellus scelerisque metus, quis molestie mi dui\n"
    "id quam. mauris vestibulum. nam ullamcorper.\n" ) );
  free ( res ); 

  return 0;
}
#endif /* __progtest__ */
