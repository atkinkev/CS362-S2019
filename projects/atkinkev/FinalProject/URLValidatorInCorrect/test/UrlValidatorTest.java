/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import junit.framework.TestCase;
import java.util.Random;

/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision$
 */
public class UrlValidatorTest extends TestCase {

	//ASSERT FUNCTIONS
	private static int assertFlag = 0;

	static public void assertFalse(String errMsg, boolean result){
    	if(result != false) {
        	System.out.println("Error: " + errMsg);
        	assertFlag++;
    	}
	}
	static public void assertTrue(String errMsg, boolean result){
    if(result != true) {
        System.out.println("Error: " + errMsg);
        assertFlag++;
    }
}
   public UrlValidatorTest(String testName) {
      super(testName);
   }
   
   /*
   * CS362 Group Tests 
   */
   
   /*
    * ************************************* UNIT TESTS START HERE ****************************************
    */
   
   // Positive Tests for protocol
  public void testIsValid_1_unit() {
	   String url = "";
	   boolean expected = false;
	   boolean result = false;
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.NO_FRAGMENTS);
	   
	   //quick fragment check
	   url = "http://www.google.com/ /";
	   result = urlVal.isValid(url);
	   assertEquals(url, false, result);
	   
	   // testing domain names
	   for (int j = 0; j < domainName.length; j++) {
		   url = "http://www." + domainName[j].item + ".com";
		   expected = domainName[j].valid;
		   result = urlVal.isValid(url);
		   assertEquals(url, expected, result);
	   }
	   
	   //testing top level domains
	   for (int j = 0; j < topLevel.length; j++) {
		   url = "http://www.google" + topLevel[j].item;
		   expected = topLevel[j].valid;
		   result = urlVal.isValid(url);
		   assertEquals(url, expected, result);
	   }
	   
	   //testing paths
	   for (int j = 0; j < sitePaths.length; j++) {
		   url = "http://www.google.com" + sitePaths[j].item;
		   expected = sitePaths[j].valid;
		   result = urlVal.isValid(url);
		   assertEquals(url, expected, result);
	   }
	   
   }
   
  // Boundary tests for url val
   public void testIsValid_2_Unit() {
	   String url = "";
	   boolean result = false;
	   boolean expected = false;
	   StringBuilder sb = new StringBuilder(20000);
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);   
	   // super long domain (but within max)
	   url = "http://www.IpledgeAllegiancetotheflagoftheUnitedStatesofAmericaandtotheRep.com";
	   result = urlVal.isValid(url);
	   assertTrue("Long domain should still validate." + url, result);
	   
	   //super duper long domain (longer than max)
	   url = "http://www.IpledgeAllegiancetotheflagoftheUnitedStatesofAmericaandtotheRepublicforwhichitstandsonenationunderGodindivisiblewithLibertyandJusticeforallIpledgeAllegiancetotheflagoftheUnitedStatesofAmericaandtotheRepublicforwhichitstandsonenationunderGodindivisiblewithLibertyandJusticeforallIpledgeAllegiancetotheflagoftheUnitedStatesofAmericaandtotheRepublicforwhichitstandsonenationunderGodindivisiblewithLibertyandJusticeforall";
	   result = urlVal.isValid(url);
	   assertFalse("Domain longer than 253 chars should fail.", result);
	   
	   // MASSIVE domain
	   sb.append("http://www.");
	   for(int i = 11; i < sb.capacity() - 4; i++) {
		   sb.append("A");
	   }
	   sb.append(".com");
	   url = sb.toString();
	   expected = false;
	   result = urlVal.isValid(url);
	   assertEquals(url, expected, result);
   }
   
   

   public static void testTest(){
	   
       UrlValidator urlVal = new UrlValidator();
       
       assertTrue(urlVal.isValid("http://www.google.com"));
       assertTrue(urlVal.isValid("http://www.google.com/pages/page1.html"));
       assertTrue(urlVal.isValid("http://www.google.com:8080"));
       assertFalse(urlVal.isValid("http://www.google.com../"));
       assertFalse(urlVal.isValid("http://www.google.invalid/"));
       assertFalse(urlVal.isValid("http://www.google.invalid./"));
       
       
   }
   
   public static void testTest2(){

       UrlValidator urlVal = new UrlValidator();

       assertTrue(urlVal.isValid("http://www.en.wikipedia.org"));
       assertTrue(urlVal.isValid("http://www.en.WiKiPEDia.org"));
       assertTrue(urlVal.isValid("http://WWW.EN.WIKIPEDIA.ORG"));
       assertTrue(urlVal.isValid("http://WWW.en.wikipedia.ORG"));
       assertFalse(urlVal.isValid("http://wwww.wikipedia.org"));
       assertFalse(urlVal.isValid("http://www.wiki_pedia.org"));
       assertFalse(urlVal.isValid("http://www. wikipedia.org"));
       assertFalse(urlVal.isValid("http://ww.wikipedia.org"));
       assertFalse(urlVal.isValid("http://ww.wikipedia.org"));
	}

	public void partitionTest1(){
        System.out.println("Partition Test # 1: ");
        assertFlag = 0;
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        //FALSE CASES
        assertFalse("Invalid: htttp://www.gmail.com", urlVal.isValid("htttp://www.gmail.com"));
        assertFalse("Invalid: h/t/t/p://www.gmail.com", urlVal.isValid("h/t/t/p://www.gmail.com"));
        //TRUE CASES
        assertTrue("Valid: http://www.gmail.com", urlVal.isValid("http://www.gmail.com"));
        assertTrue("Valid: https://www.gmail.com", urlVal.isValid("https://www.gmail.com"));

        if(assertFlag > 0) {
            fail("Partition Test #1 Failure");
        } else {
            System.out.println("Partition Test #1 Successful!");
        }
	}
	public void partitionTest2(){
	    System.out.println("Partition Test #2: ");
	    assertFlag = 0;
	    UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	    //FALSE CASES
	    assertFalse("Invalid: http://www.---.com", urlVal.isValid("http://www.---.com"));
	    assertFalse("Invalid: http://www.oregonstate", urlVal.isValid("http://www.oregonstate"))
	    assertFalse("Invalid: www/oregonstate/edu", urlVal.isValid("www/oregonstate/edu"));
	    //TRUE CASES
	    assertTrue("Valid: http://www.oregonstate.edu", urlVal.isValid("http://www.gmail.com"));
	    assertTrue("Valid: https://www.gmail.com", urlVal.isValid("https://www.gmail.com"));
	    assertTrue("Valid: https://www.reddit.com", urlVal.isValid("https://www.reddit.com"));

	    if(assertFlag > 0) {
	        fail("Partition Test #2 Failure");
	    } else {
	        System.out.println("Partition Test #2 Successful!");
	    }
	}
	public void partitionTest3(){
        System.out.println("Partition Test #3: ");
        assertFlag = 0;
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        //FALSE CASES
        assertFalse("Invalid: http://www.google.com:port#", urlVal.isValid("http://www.google.com:port#"));
        assertFalse("Invalid: http://www.google.com:-1", urlVal.isValid("http://www.google.com:-1"));
        assertFalse("Invalid: http://www.google.com:sftp", urlVal.isValid("http://www.google.com:sftp"));
        //TRUE CASES
        assertTrue("Valid: http://www.google.com:80", urlVal.isValid("http://www.google.com:80"));
        assertTrue("Valid: http://www.reddit.com:80", urlVal.isValid("http://www.reddit.com:80"));
        assertTrue("Valid: http://www.oregonstate.edu:80", urlVal.isValid("http://www.oregonstate.edu:80"));

        if(assertFlag > 0) {
            fail("Partition Test #3 Failure");
        } else {
            System.out.println("Partition Test #3 Successful!");
        }
	}
	public void partitionTest4(){
        System.out.println("Partition Test # 4: ");
        assertFlag = 0;
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        //FALSE CASES
        assertFalse("Invalid: htttp://www.gmail.com", urlVal.isValid("htttp://www.gmail.com"));
        assertFalse("Invalid: h/t/t/p://www.gmail.com", urlVal.isValid("h/t/t/p://www.gmail.com"));
        //TRUE CASES
        assertTrue("Valid: http://www.gmail.com", urlVal.isValid("http://www.gmail.com"));
        assertTrue("Valid: https://www.gmail.com", urlVal.isValid("https://www.gmail.com"));

        if(assertFlag > 0) {
            fail("Partition Test #4 Failure");
        } else {
        	System.out.println("Partition Test #4 Successful!");
        }
	}
	public void partitionTest5(){
        System.out.println("Partition Test #5: ");
        assertFlag = 0;
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        //FALSE CASES
        assertFalse("Invalid: http://www.reddit.com/--..,/", urlVal.isValid("http://www.reddit.com/--..,/"));
        assertFalse("Invalid: http://www.reddit.com/bad///path", urlVal.isValid("Invalid: http://www.reddit.com/bad///path"));
        //TRUE CASES
        assertTrue("Valid: http://www.reddit.com/r/osuonlinecs", urlVal.isValid("http://www.reddit.com/r/osuonlinecs"));
        assertTrue("Valid: https://oregonstate.edu/about", urlVal.isValid("https://oregonstate.edu/about"));

        if(assertFlag > 0) {
            fail("Partition Test #5 Failure");
        } else {
            System.out.println("Partition Test #5 Successful!");
        }
	}
	public void partitionTest6(){
        System.out.println("Partition Test # 6: ");
        assertFlag = 0;
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        //FALSE CASES
        assertFalse("Invalid: https://www.reddit.com/search/!?q1=1", urlVal.isValid("https://www.reddit.com/search/!?q1=1"));
        assertFalse("Invalid: https://www.reddit.com/search/   ?q=osu", urlVal.isValid("https://www.reddit.com/search/   ?q=osu"));
        //TRUE CASES
        assertTrue("Valid: https://www.reddit.com/search/?q=oregon%20state", urlVal.isValid("https://www.reddit.com/search/?q=oregon%20state"));
        assertTrue("Valid: https://search.oregonstate.edu/?q=new+students&close=default_frontend", urlVal.isValid("https://search.oregonstate.edu/?q=new+students&close=default_frontend"));

        if(assertFlag > 0) {
            fail("Partition Test #6 Failure");
        } else {
            System.out.println("Partition Test #6 Successful!");
        }
	}

   ResultPair[] protocol = {new ResultPair("http", true),
           new ResultPair("https", true),
           new ResultPair("httpd", true)};
   
   ResultPair[] domainName = {new ResultPair("amazon", true), 
		   new ResultPair("\\.\\google", false),	// leading wacky characters
		   new ResultPair("/\\/\\yahoo", false), 	// more leading wacky characters
		   new ResultPair("g.o..o.g.l.e", false),	// dots in the domain
		   new ResultPair("--google", false),		// begins with dash
		   new ResultPair("google--", false),
		   new ResultPair("g!o!o!g!l!e", false),	// excited google, invalid char
		   new ResultPair("aliens", true)};			// arbitrary valid
   
   ResultPair[] topLevel = {new ResultPair(".probablyNotValid", false),
		   new ResultPair(".**definitelyNotValid", false),	// leading bad chars
		   new ResultPair(".net", true),
		   new ResultPair(".us", true),		// some classics
		   new ResultPair(".fr", true),
		   new ResultPair(".com", true)};
   
   ResultPair[] sitePaths = {new ResultPair("/r/programming", true),
		   new ResultPair("/views/Kevin\\sProfile", false),		// invalid char
		   new ResultPair("/animals/chipmunk/", true),
		   new ResultPair("/path?name=Kevin", true)};		//invalid query string?
		   
		   
	/*
	************************************* RANDOM TESTS START HERE *********************************************
	*/
	
	 /*
   * CS362 Group Tests 
   */
   // Positive Random Tests for protocol
  public void testIsValid_1() {
	  boolean result = false;
	  int appendChar = -1;
	  Random r = new Random();
	  UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES); 
	  
	  String url = "";
	  StringBuilder sb = new StringBuilder(20);
	  String safeChars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	  String reservedChars = "; / ? : @ = &";
	  
	  // Randomly generate domains with safe chars
	  for(int i = 0; i < 1000; i++) {
		  for (int j = 0; j < 20; j++) {
			  appendChar = r.nextInt(safeChars.length());
			  sb.append(safeChars.charAt(appendChar));
		  }
		  url = "http://www." + sb.toString() + ".com";	
		  result = urlVal.isValid(url);
		  assertTrue("Random safe domain should validate.", result);
		  sb.setLength(0);
	  }
	  
	  // Randomly generate domains with reserved/safe chars
	  for(int i = 0; i < 1000; i++) {
		  for (int j = 0; j < 20; j++) {
			  appendChar = r.nextInt(reservedChars.length());
			  sb.append(reservedChars.charAt(appendChar));
			  appendChar = r.nextInt(safeChars.length());
			  sb.append(safeChars.charAt(appendChar));
		  }
		  url = "http://www." + sb.toString() + ".com";
		  result = urlVal.isValid(url);
		  assertFalse("URL full of reserved chars should not validate.", result);
		  sb.setLength(0);
	  }
   }
   
  // Test random portnums
   public void testIsValid_2() {
	   boolean result = false;
	   boolean expected = false;
	   Random r = new Random();
	   int portNum = -1;
	   String url = "";
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES); 
	
	   // testing positive port nums
	   for (int i = 0; i < 1000; i++) {
		   portNum = r.nextInt(150000);
		   if (portNum > 65535 || portNum < 1) {
			   expected = false;
		   }
		   else {
			   expected = true;
		   }   
		   url = "http://google.com:" + portNum;
		   result = urlVal.isValid(url);
		   assertEquals("Port number within range should validate.", expected, result);
	   }
	   
	   for (int i = 0; i < 1000; i++) {
		   portNum = r.nextInt(150000) * -1;
		   expected = false;

		   url = "http://google.com:" + portNum;
		   result = urlVal.isValid(url);
		   assertEquals("Port number within range should validate.", expected, result);
	   }

   }
   
   public void testIsValid_3() {
	   boolean result = false;
	   boolean expected = false;
	   String url = "";
	   int randomOctet = -1;
	   Random r = new Random();
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);  
	   
	   for (int i = 0; i < 1000; i++) {
		   expected = true;
		   url = "";
		   for (int j = 0; j < 4; j++) {
			   randomOctet = r.nextInt(500);
			   if (randomOctet > 255) {
				   expected = false;
			   }
			   if (j < 3) {
				   url += randomOctet + ".";
			   }
			   else {
				   url += randomOctet + "";
			   }
		   }
		   url = "http://" + url;
		   result = urlVal.isValid(url);
		   assertEquals(url, expected, result);
	   }
   }


   public static String randomStringMixed() {
       
        int leftLimit = 33; // letter '!'
        int rightLimit = 122; // letter '`'
        int targetStringLength = 7;
        Random random = new Random();
        StringBuilder buffer = new StringBuilder(targetStringLength);
        for (int i = 0; i < targetStringLength; i++) {
            int randomLimitedInt = leftLimit + (int)
              (random.nextFloat() * (rightLimit - leftLimit + 1));
            buffer.append((char) randomLimitedInt);
        }
        String generatedString = buffer.toString();
    
        return generatedString;
    }
   
   
   public static String randomStringShort() {
       
        int leftLimit = 97; // letter 'a'
        int rightLimit = 122; // letter 'z'
        int targetStringLength = 7;
        Random random = new Random();
        StringBuilder buffer = new StringBuilder(targetStringLength);
        for (int i = 0; i < targetStringLength; i++) {
            int randomLimitedInt = leftLimit + (int)
              (random.nextFloat() * (rightLimit - leftLimit + 1));
            buffer.append((char) randomLimitedInt);
        }
        String generatedString = buffer.toString();
    
        return generatedString;
    }
   
   public static String randomStringLong() {
       
        int leftLimit = 97; // letter 'a'
        int rightLimit = 122; // letter 'z'
        int targetStringLength = 500;
        Random random = new Random();
        StringBuilder buffer = new StringBuilder(targetStringLength);
        for (int i = 0; i < targetStringLength; i++) {
            int randomLimitedInt = leftLimit + (int)
              (random.nextFloat() * (rightLimit - leftLimit + 1));
            buffer.append((char) randomLimitedInt);
        }
        String generatedString = buffer.toString();
    
        return generatedString;
    }
 
   
   
   public static void testMixedUrl() {
       
       String url = "";
       String domain = "";
       
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       
       for(int i=0; i<1000; i++) {
           
           domain = randomStringMixed();
           
           url = "http://www." + domain + ".com";
           
           try{
        	   urlVal.isValid(url);
           }
           catch (Exception e) {
        	   fail("Should not throw exceptions for any combination of chars.");
           }
       }

   }
   
   
   public static void testShortUrl() {
       
       String url = "";
       String domain = "";
       
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       
       for(int i=0; i<1000; i++) {
           
           domain = randomStringShort();
           
           url = "http://www." + domain + ".com";
           
           assertTrue(urlVal.isValid(url));
       }

   }
   
   
   public static void testLongUrl() {
       
       String url = "";
       String domain = "";
       
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       
       for(int i=0; i<1000; i++) {
           
           domain = randomStringLong();
           
           url = "http://www." + domain + ".com";
           
           try{
        	   urlVal.isValid(url);
           }
           catch (Exception e) {
        	   fail("Should not throw exceptions for any combination of chars.");
           }
       }

       
   }
	

}