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
import java.util.UUID;


/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {

    String[] validUrls = {"http://foo.com/blah_blah",
                          "http://foo.com/blah_blah/",
                          "http://www.example.com/wpstyle/?p=364",
                          "https://www.example.com/foo/?bar=baz&inga=42&quux",
                          "http://userid@example.com:8080",
                          "http://142.42.1.1/",
                          "ftp://foo.bar/baz",
                          "http://a.b-c.de",
                          "http://foo.bar/?q=Test%20URL-encoded%20stuff",
                          "http://foo.com/blah_(wikipedia)_blah#cite-1"
                         };

    String[] invalidUrls = {"http://",
                            "http://??",
                            "http://3628126748",
                            "http:// shouldfail.com",
                            "http://-error-.invalid/",
                            "http://userid:password@example.com:8080",                            
                            "http://foo.bar?q=Spaces should be encoded",
                            "foo.com",
                            "ftps://foo.bar/"
                          };

	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
     boolean validity;

     for(int i=0; i<validUrls.length; i++){
        System.out.println("\nTesting valid url: "+validUrls[i]);
        validity = urlVal.isValid(validUrls[i]);
        if(validity){
          System.out.println("PASS\n");
        }else{
          System.out.println("FAIL\n");
        }
     }
     System.out.println();

    for(int i=0; i<invalidUrls.length; i++){
        System.out.println("\nTesting invalid url: "+invalidUrls[i]);
        validity = urlVal.isValid(invalidUrls[i]);
        if(validity){
            System.out.println("PASS\n");
        }else{
            System.out.println("FAIL\n");
        }
    }

	   System.out.println("\nTest Finished Successfully.\n\n");
	   
	   
   }

   // Partitions will be the prefix of a URL, a random string, and then the postfix of a URL
   // Example:  "www." + "dalfkdfwi" + ".com"

    String[] PrefixPartition = { "http://",
                                "https://",
                                "www.",
                                "http://www.",
                                "https://www.",
                                "",
                                "ftp://",
                                "https://",
                                "http://"
                              };

    String[] PostfixPartition = { ".com",
                                  ".net",
                                  ".org",
                                  ".com/",
                                  ".edu",
                                  ".gov",
                                  ".net/",
                                  ".org/",
                                  ".edu/"
                                };

    String[] PathPartition = {  "/abc",
                                "/abc/",
                                "/abc/def",
                                "",
    };
   
   public String randomString(){
        String uuid = UUID.randomUUID().toString().replaceAll("-", "");
        System.out.println("uuid = " + uuid);

        return uuid;
   }
   
   public void testYourFirstPartition()
   {
        System.out.println("Testing the first partition: prefix\n");
        UrlValidator url = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        String randomString = randomString();
        int num = 9;  //current number of partitions 

        for(int i = 0; i < num ; i++){
          String randomUrl = PrefixPartition[i] + randomString + ".com";
          System.out.println("\nURL after partition test: " + randomUrl + "\n");
          boolean result = url.isValid(randomUrl);

          if(result){
            System.out.println(randomUrl + " URL is valid. PASS.\n");
          } else{
            System.out.println(randomUrl + " URL is invalid. FAIL.\n");
          }

        }
	   
   }
   
   public void testYourSecondPartition(){

        System.out.println("Testing the second partition: postfix\n");

        UrlValidator url = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        String randomString = randomString();
        int num = 9;  //current number of partitions 

        for(int i = 0; i < num ; i++){
          String randomUrl = "http://www." + randomString + PostfixPartition[i];
          System.out.println("URL after partition test: " + randomUrl + "\n");
          boolean result = url.isValid(randomUrl);

          if(result){
            System.out.println(randomUrl + " URL is valid. PASS.\n");
          } else{
            System.out.println(randomUrl + " URL is invalid. FAIL.\n");
          }

        }
   }
   
   /*do programming based testing. Write few unit test cases. You can have some
   sort of loop in your unit test and test different URL with each instance of
   the loop. Something very similar to testIsValid() but your own logic and
   idea. Even a single test will be sufficient if you write it like
   testIsValid() method.*/
   
   public void testIsValid()
   {

    String[] validScheme = {"http://", "https://", "ftp://"};
    String[] validAuthority = {"www.example.com", "thisgood.com", "alsothis.org"};
    String[] validPath = {"/abc", "/abc/", "/abc/def"};
    String[] validQuery = {"?foo=bar", ""};

    int bugs = 0;

	   for(int i = 0;i<10000;i++)
	   {
		      int schemeR = (int)(Math.random()*3);
          int authR = (int)(Math.random()*3);
          int pathR = (int)(Math.random()*3); 
          int queryR = (int)(Math.random()*2);

          String testUrl = validScheme[schemeR] + validAuthority[authR] + validPath[pathR] + validQuery[queryR];
          UrlValidator url = new UrlValidator();

          boolean result = url.isValid(testUrl);

          if(result==false){
            bugs++;
          }
	   }

     System.out.println("\nNumber of bugs in testIsValid: " + bugs + "\n");
   }
   
   public void testAnyOtherUnitTest()
   {
	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   

}
