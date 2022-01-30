//
// Used the following C# linq pad statement to strip and save
// the 5 letter words.
//
// Download the word database from: https://www.curlewcommunications.uk/wordlist.html
//
//

string inpath = @"C:\Users\richa\Downloads\british\brit-a-z.txt";
List<string> mylist = new List<string>();

foreach(string line in System.IO.File.ReadLines(inpath))
{
	line.Trim();
	if(line.Length != 5)
		continue;
		
	// remove non ascii char
	System.Text.RegularExpressions.Regex reg = new Regex(@"[\W\d]");
	if(reg.IsMatch(line))
	{
		Console.WriteLine(line);
		continue;
	}
	
		
	var new_line = line.ToUpper();	
	mylist.Add(new_line);
}

var rnd = new Random();
var randomized = mylist.OrderBy(m => rnd.Next());
mylist.Count().Dump();

System.IO.File.WriteAllLines(@"c:\temp\words5.txt", randomized);