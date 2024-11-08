import java.io.BufferedReader;
import java.util.HashMap;

import acmx.export.java.io.FileReader;

/*
 * File: NameSurferDataBase.java
 * -----------------------------
 * This class keeps track of the complete database of names.
 * The constructor reads in the database from a file, and
 * the only public method makes it possible to look up a
 * name and get back the corresponding NameSurferEntry.
 * Names are matched independent of case, so that "Eric"
 * and "ERIC" are the same names.
 */

public class NameSurferDataBase implements NameSurferConstants {

	/* Constructor: NameSurferDataBase(filename) */
	/**
	 * Creates a new NameSurferDataBase and initializes it using the data in the
	 * specified file. The constructor throws an error exception if the requested
	 * file does not exist or if an error occurs as the file is being read.
	 */
	public NameSurferDataBase(String filename) {
		try {
			/** read every line from file with bufferreader rd */
			BufferedReader rd = new BufferedReader(new FileReader(filename));
			while (true) {
				String line = rd.readLine();
				/** if linedoesn't exist anymore, while should break */
				if (line == null) {
					break;
				}
				/**
				 * give already read line to NameSurferEntry Class to put ranks into array and
				 * name to appropriate string.
				 */
				NameSurferEntry entry = new NameSurferEntry(line);
				/**
				 * with NameSurferEntry Class array help, we make HashMap where key is name,
				 * value is entry itself.
				 */
				map.put(entry.getName(), entry);
			}
			rd.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/* Method: findEntry(name) */
	/**
	 * Returns the NameSurferEntry associated with this name, if one exists. If the
	 * name does not appear in the database, this method returns null.
	 */
	public NameSurferEntry findEntry(String name) {
		return map.get(name);
	}

	private HashMap<String, NameSurferEntry> map = new HashMap<>();
}
