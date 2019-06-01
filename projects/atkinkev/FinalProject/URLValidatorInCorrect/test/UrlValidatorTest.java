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

   public UrlValidatorTest(String testName) {
      super(testName);
   }
   
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

}


