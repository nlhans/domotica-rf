using System;
using System.IO;
using System.Linq;
using System.Text;

namespace PackTool
{
    class Program
    {
        const string contentPath = @"C:\Projects\Firmware\domoticarf\web\Content\";

        private static byte[] flashArray = new byte[512*1024];

        public static string exportList = "";
        public static int offset = 0;

        public static void addFile(string file)
        {
            byte[] content = File.ReadAllBytes(contentPath + file);

            exportList += file + "@" + offset + "\r\n";

            // Add inside the FLASH:
            // File content length
            // File type length
            // File type string
            // File content
            string fileType = MimeType.GetMimeType(Path.GetExtension(file));

            byte[] bContentLength = BitConverter.GetBytes((ushort)content.Length);
            byte[] fTypeLength = BitConverter.GetBytes((ushort)fileType.Length);
            byte[] fType = ASCIIEncoding.ASCII.GetBytes(fileType);

            Array.Copy(bContentLength, 0, flashArray, offset, 2);
            offset += 2;
            Array.Copy(fTypeLength, 0, flashArray, offset, 2);
            offset += 2;
            Array.Copy(fType, 0, flashArray, offset, fType.Length);
            offset += fType.Length;
            Array.Copy(content, 0, flashArray, offset, content.Length);
            offset += content.Length;
        }

        static void Main(string[] args)
        {
            for (var i = 0; i < flashArray.Length; i++)
                flashArray[i] = 0xFF;
            
            addFile("favicon.ico");

            File.WriteAllBytes("flash.bin", flashArray);
        }
    }
}
