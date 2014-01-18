using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace XC16MapBeautifier
{
    struct allocationInfo
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

            extractAllocations(allocationsRAM, lines, lineIndex_RAM);
            extractAllocations(allocationsFLASH, lines, lineIndex_FLASH);

            extractSizes(ramStart,ref allocationsRAM);
            extractSizes(flashStart,ref allocationsFLASH);

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
