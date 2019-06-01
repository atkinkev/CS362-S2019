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
   // Positive Tests for protocol
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
	  
	  // Randomly generate domains with reserved chars
	  for(int i = 0; i < 1000; i++) {
		  for (int j = 0; j < 20; j++) {
			  appendChar = r.nextInt(reservedChars.length());
			  sb.append(reservedChars.charAt(appendChar));
		  }
		  url = "http://www." + sb.toString() + ".com";
		  result = urlVal.isValid(url);
		  assertFalse("URL full of reserved chars should not validate.", result);
		  sb.setLength(0);
	  }
   }
   
  // Boundary tests for url val
   public void testIsValid_2() {

	   return;
   }

}


