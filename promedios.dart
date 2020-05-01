import 'dart:io';
import 'dart:async';
import 'dart:convert';
import 'package:csv/csv.dart';

main(List arguments) {
  final File file = new File(arguments[0]);
  File promediosCSV = new File("promediosDart.csv");

  Stream<List> inputStream = file.openRead();
  inputStream
      .transform(utf8.decoder)       // Decode bytes to UTF-8.
      .transform(new LineSplitter()) // Convert stream to individual lines.
      .listen((String line) {        // Process results.

       List row = line.split(';');

        String rut = row[0];
        var nem = double.parse(row[1]);
        var ranking = double.parse(row[2]);
        var matematica = double.parse(row[3]);
        var lenguaje = double.parse(row[4]);
        var ciencia = double.parse(row[5]);
        var historia = double.parse(row[6]);
        double promedio = (nem+ranking+matematica+lenguaje+ciencia+historia)/6;
        promediosCSV.writeAsStringSync("${rut}, ${promedio}\r\n", mode: APPEND);
      },
      onDone: () { print('El archivo ahora esta cerrado.'); },
      onError: (e) { print(e.toString()); });
  
}