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
   public void testIsValid_2() {
	   String url = "";
	   boolean result = false;
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);   
	   // super long domain (but within max)
	   url = "http://www.IpledgeAllegiancetotheflagoftheUnitedStatesofAmericaandtotheRep.com";
	   result = urlVal.isValid(url);
	   assertTrue("Long domain should still validate." + url, result);
	   
	   url = "http://www.IpledgeAllegiancetotheflagoftheUnitedStatesofAmericaandtotheRepublicforwhichitstandsonenationunderGodindivisiblewithLibertyandJusticeforallIpledgeAllegiancetotheflagoftheUnitedStatesofAmericaandtotheRepublicforwhichitstandsonenationunderGodindivisiblewithLibertyandJusticeforallIpledgeAllegiancetotheflagoftheUnitedStatesofAmericaandtotheRepublicforwhichitstandsonenationunderGodindivisiblewithLibertyandJusticeforall";
	   result = urlVal.isValid(url);
	   assertFalse("Domain longer than 253 chars should fail.", result);
	   return;
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

}