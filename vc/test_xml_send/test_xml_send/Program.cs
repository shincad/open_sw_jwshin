using System;
using System.Net;
using System.IO;

namespace test_xml_send
{
    class Program
    {
        static public void sendFileToWebservice()
        {
            string xmlString = System.IO.File.ReadAllText("test.xml");
            string url = "http://localhost:3901";
            HttpWebRequest req = (HttpWebRequest)WebRequest.Create(url);


            byte[] requestBytes = System.Text.Encoding.ASCII.GetBytes(xmlString);
            req.Method = "POST";
            req.ContentType = "text/xml;charset=utf-8";
            req.ContentLength = requestBytes.Length;
            Stream requestStream = req.GetRequestStream();
            requestStream.Write(requestBytes, 0, requestBytes.Length);
            requestStream.Close();

            HttpWebResponse res = (HttpWebResponse)req.GetResponse();
            StreamReader sr = new StreamReader(res.GetResponseStream(), System.Text.Encoding.Default);
            string backstr = sr.ReadToEnd();
            //Console.WriteLine(backstr);
            sr.Close();
            res.Close();
        }

        static public void HTTPost()
        {
            string sParam = System.IO.File.ReadAllText("test.xml");
            string sUrl = "http://localhost:3901";
            //string sUrl = "http://10.10.10.130:3901";
            WebRequest webRequest = WebRequest.Create(sUrl);
            webRequest.Method = "POST";
            byte[] bytearray = System.Text.Encoding.UTF8.GetBytes(sParam);
            webRequest.ContentType = "application/x-www-form-urlencoded";
            //webRequest.ContentType = "text/xml;charset=utf-8";
            webRequest.ContentLength = bytearray.Length;
            Stream stream = webRequest.GetRequestStream();
            stream.Write(bytearray, 0, bytearray.Length);
            stream.Close();

            WebResponse webResponse = webRequest.GetResponse();

            stream = webResponse.GetResponseStream();
            StreamReader streamReader = new StreamReader(stream);
            string sReturn = streamReader.ReadToEnd();
            Console.WriteLine("Return Value : ");
            Console.WriteLine();
            Console.WriteLine(sReturn);

            streamReader.Close();
            stream.Close();
            webResponse.Close();
         
        }

       
        static void Main(string[] args)
        {

            //sendFileToWebservice();
            HTTPost();
            Console.WriteLine();
            Console.WriteLine("dnp agent! send xml Code~!!!! ");
        }
    }
}
