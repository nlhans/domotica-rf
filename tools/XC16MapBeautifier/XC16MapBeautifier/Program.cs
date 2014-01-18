using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.IO;

namespace XC16MapBeautifier
{
    public class  allocationInfo
    {
        public int location;
        public int size;

        public string file;
    }

    class Program
    {
        static void Main(string[] args)
        {
            var ramStart=0x0800;
            var flashStart=0x0200;
            
        Dictionary<string, allocationInfo> allocationsRAM = new Dictionary<string, allocationInfo>();
        Dictionary<string, allocationInfo> allocationsFLASH = new Dictionary<string, allocationInfo>();
        

            string file = @"C:\Projects\Firmware\domoticarf\targets\mrf49xa_pic24\dist\default\production\mrf49xa_pic24.production.map";

            var lines = File.ReadAllLines(file).ToList();
            for (int i = 0; i < lines.Count; i++) lines[i] = lines[i].Trim();

            int lineIndex_RAM = lines.IndexOf("External Symbols in Data Memory (by address):")+2;
            int lineIndex_FLASH = lines.IndexOf("External Symbols in Program Memory (by address):")+2;
            int detailedAllocations = lines.IndexOf("__c30_signature");

            extractAllocations(allocationsRAM, lines, lineIndex_RAM);
            extractAllocations(allocationsFLASH, lines, lineIndex_FLASH);

            extractSizes(ramStart,ref allocationsRAM);
            extractSizes(flashStart,ref allocationsFLASH);

            // Extract detailed allocations.
            string activeFile = "";
            while(true)
            {
                if (lines.Count <= detailedAllocations) break;

                var line = lines[detailedAllocations];
                detailedAllocations++;

                var data = line.Replace(" ","").Split("_".ToCharArray(), 2);
                if (data.Length == 1) continue;

                if(data[0].Length>10)
                {
                    // It is a new file.
                    activeFile = Path.GetFileName(data[1]);
                }else
                {
                    var method = data[1];
                    if(allocationsRAM.ContainsKey(method)) allocationsRAM[method].file = activeFile;
                    if(allocationsFLASH.ContainsKey(method)) allocationsFLASH[method].file = activeFile;
                }

            }


            string statsPerFile = "<table><tr><td>File</td><td>RAM</td><td>Flash</td></tr>";
            string ramUsageByFile = "<table><tr><td>File</td><td>Allocation</td><td>Location</td><td></td><td>Size</td><td></td></tr>";
            string ramUsageBySize = "<table><tr><td>Allocation</td><td>Location</td><td></td><td>Size</td><td></td><td>File</td></tr>";
            string flashUsageByFile = "<table><tr><td>File</td><td>Allocation</td><td>Location</td><td></td><td>Size</td><td></td></tr>";
            string flashUsageBySize = "<table><tr><td>Allocation</td><td>Location</td><td></td><td>Size</td><td></td><td>File</td></tr>";

            foreach (var alloc in allocationsRAM.OrderBy(x => 0 - x.Value.size))
                ramUsageBySize += string.Format("<tr><td>{0}</td><td>{1}</td><td>(0x{1:X})</td><td>{2}</td><td>(0x{1:X})</td><td>{3}</td></tr>\r\n", alloc.Key, alloc.Value.location, alloc.Value.size, alloc.Value.file);
            
            foreach (var alloc in allocationsFLASH.OrderBy(x => 0 - x.Value.size))
                flashUsageBySize+= string.Format("<tr><td>{0}</td><td>{1}</td><td>(0x{1:X})</td><td>{2}</td><td>(0x{1:X})</td><td>{3}</td></tr>\r\n", alloc.Key, alloc.Value.location, alloc.Value.size, alloc.Value.file);

            Dictionary<string, int> ramPerFile = new Dictionary<string, int>();
            Dictionary<string, int> flashPerFile = new Dictionary<string, int>();

            // Ram per file
            foreach (var f in allocationsRAM.OrderBy(x => x.Value.file + "_" + x.Key).GroupBy(x => x.Value.file))
            {
                var totalSize = 0;

                ramUsageByFile += "<tr><td><h4><a id=\"ram"+f.Key+"\">" + f.Key + "</a></td></tr>";
                foreach (var alloc in f)
                {
                    ramUsageByFile += string.Format("<tr><td>{3}</td><td>{0}</td><td>{1}</td><td>(0x{1:X})</td><td>{2}</td><td>(0x{1:X})</td></tr>\r\n", alloc.Key, alloc.Value.location, alloc.Value.size, alloc.Value.file);
                    totalSize += alloc.Value.size;
                }
                ramUsageByFile += "<tr><td>Total</td><td></td><td></td><td></td><td>" + totalSize + "</td><td>bytes</td></tr>";
                ramUsageByFile += "<tr><td></td></tr>";
                if(ramPerFile.ContainsKey(f.Key)==false)ramPerFile.Add(f.Key, totalSize);
            }

            // Flash per file
            foreach (var f in allocationsFLASH.OrderBy(x => x.Value.file + "_" + x.Key).GroupBy(x => x.Value.file))
            {
                var totalSize = 0;

                flashUsageByFile += "<tr><td><h4><a id=\"flash" + f.Key + "\">" + f.Key + "</td><td></td><td></td><td></td><td></td><td></td></tr>";
                foreach (var alloc in f)
                {
                    flashUsageByFile += string.Format("<tr><td>{3}</td><td>{0}</td><td>{1}</td><td>(0x{1:X})</td><td>{2}</td><td>(0x{1:X})</td></tr>\r\n", alloc.Key, alloc.Value.location, alloc.Value.size, alloc.Value.file);
                    totalSize += alloc.Value.size;
                }
                flashUsageByFile += "<tr><td>Total</td><td></td><td></td><td></td><td>" + totalSize + "</td><td>bytes</td></tr>";
                flashUsageByFile += "<tr><td></td></tr>";
                if(flashPerFile.ContainsKey(f.Key ?? string.Empty)==false)flashPerFile.Add(f.Key ?? string.Empty, totalSize);

            }

            // Stats per file
            var totalRam = 0;
            var totalFlash = 0;
            var files = ramPerFile.Keys.Concat(flashPerFile.Keys).Distinct();
            foreach(var f in files.OrderBy(x=>x))
            {
                var ram = ((ramPerFile.ContainsKey(f)) ? ramPerFile[f] : 0);
                var flash = ((flashPerFile.ContainsKey(f)) ? flashPerFile[f] : 0);
                totalRam += ram;
                totalFlash += flash;
                statsPerFile += "<tr><td>" + f + "</td><td><a href=\"#ram" + f + "\">" + ram + "</td><td><a href=\"#flash" + f + "\">" + flash + "</td></tr>";
            }
            statsPerFile += "<tr><td>Total</td><td>" + totalRam + "</td><td>" + totalFlash + "</td></tr>";

            ramUsageByFile += "</table>";
            ramUsageBySize += "</table>";
            flashUsageByFile += "</table>";
            flashUsageBySize += "</table>";
            statsPerFile += "</table>";

            string htmlPage = "<h1>Linker map beautifier</h1><h2>Stats per file</h2>"+statsPerFile+
                "<h2>RAM usage</h2><h3>By File</h3>" + ramUsageByFile +"<h3>By Size</h3>" + ramUsageBySize +
            "<h2>Flash usage</h2><h3>By File</h3>" + flashUsageByFile + "<h3>By Size</h3>" + flashUsageBySize;

            File.WriteAllText("linker.html", htmlPage);
            Process.Start("linker.html");
        }

        private static void extractSizes(int start, ref Dictionary<string, allocationInfo> allocs)
        {
            var sortedAllocList = allocs.OrderByDescending(x => 0 - x.Value.location).Select(x => x.Key);

            var previousPoint = start;
            var previousKey = string.Empty;
            foreach (var k in sortedAllocList)
            {
                if (previousKey != string.Empty)
                {
                    var prevAlloc = allocs[previousKey];
                    prevAlloc.size = allocs[k].location - prevAlloc.location;
                    allocs[previousKey] = prevAlloc;
                }
                previousKey = k;
            }
        }

        private static void extractAllocations(Dictionary<string, allocationInfo> alloc, List<string> lines, int point)
        {
            while (true)
            {
                var line = lines[point];
                if (line == "") break;
                line = line.Replace(" ", "");
                var data = line.Split("_".ToCharArray(), 2);
                if (data[0].Substring(0, 2) == "0x")
                {
                    data[0] = data[0].Substring(2);
                    var location = int.Parse(data[0], System.Globalization.NumberStyles.HexNumber);

                    var allocation = new allocationInfo();
                    allocation.location = location;

                    alloc.Add(data[1], allocation);
                    point++;
                }
                else
                {
                    Console.WriteLine("Unexpected line at index " + point + " : " + line);
                    break;
                }
            }
        }
    }
}
