package ru.nsu.kolochkin.Befunge;

import java.io.FileReader;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;
import java.util.Stack;

public class Parser {
	Parser() {
		map.put('\\', "ChangerVertexes");
		map.put('\'', "Comparison");
		map.put(':', "CopierVertex");
		map.put('"', "SymbolMode");
		map.put('$', "Deleter");
		map.put('/', "Division");
		map.put('!', "Invert");
		map.put('-', "Minus");
		map.put('%', "Mod");
		map.put('*', "Multiplication");
		map.put('.', "NumberPrint");
		map.put('+', "Plus");
		map.put(',', "SymbolPrint");
		map.put('~', "SymbolRequest");
		map.put('0', "Constant");
		map.put('1', "Constant");
		map.put('2', "Constant");
		map.put('3', "Constant");
		map.put('4', "Constant");
		map.put('5', "Constant");
		map.put('6', "Constant");
		map.put('7', "Constant");
		map.put('8', "Constant");
		map.put('9', "Constant");
		map.put('>', "Direction");
		map.put('<', "Direction");
		map.put('^', "Direction");
		map.put('v', "Direction");
		map.put('_', "Direction");
		map.put('|', "Direction");
		map.put('?', "Direction");
		map.put('#', "Direction");
		map.put('p', "Put");
		map.put('g', "Get");
		map.put(' ', "Empty");
		map.put('@', "End");
	}

	private static ArrayList<ArrayList<Character>> field = new ArrayList<>();

	private static Stack<Character> stack = new Stack<>();

	private static HashMap<Character, String> map = new HashMap<>();

	private static CommandFactory factory = new CommandFactory();

	private static String filePath = "/Users/deniskolockin" +
									 "/IdeaProjects/Befunge" +
									 "/src/ru/nsu/kolochkin/Befunge/fib.txt";

	private static int x;

	private static int y;

	private static Character direction = '>';

	private static boolean end = false;

	public static void changeDirection(Character command) {
		if (command.equals('_')) {
			if(stack.pop() == 0) {
				direction = '>';
				return;
			}
			else {
				direction = '<';
				return;
			}
		}
		if (command.equals('|')) {
			if(stack.pop() == 0) {
				direction = 'v';
				return;
			}
			else {
				direction = '^';
				return;
			}
		}
		if (command.equals('?')) {
			char[] directions = {'^', '<', '>', 'v'};
			int index = (int) (Math.random() * 3);
			direction = directions[index];
			return;
		}
		if (command.equals('#')) {
			move();
			return;
		}
		direction = command;
	}

	public static void pushSymbols() {
		move();
		while (!field.get(y).get(x).equals('"')) {
			stack.push(field.get(y).get(x));
			move();
		}
	}

	public static void move() {
		if (direction.equals('>')) {
			x += 1;
			if (x >= 80) {
				x -= 80;
			}
		}
		if (direction.equals('<')) {
			x -= 1;
			if (x < 0) {
				x += 80;
			}
		}
		if (direction.equals('^')) {
			y -= 1;
			if (y < 0) {
				y += 25;
			}
		}
		if (direction.equals('v')) {
			y += 1;
			if (y >= 25) {
				y -= 25;
			}
		}
	}

	public static void parse() {
		while(!end) {
			execute(map.get(field.get(y).get(x)), field.get(y).get(x));
			move();
		}
	}

	public static void read() {
		try (FileReader fr = new FileReader(filePath)) {
			Scanner scanner = new Scanner(fr);
			int countY = 0;
			while (scanner.hasNextLine()) {
				String tmp = scanner.nextLine();
				ArrayList<Character> l = new ArrayList<>();
				for (int i = 0; i < tmp.length(); i++) {
					l.add(tmp.charAt(i));
				}
				for (int i = tmp.length(); i < 80; i++) {
					l.add(' ');
				}
				field.add(l);
				countY++;
			}
			ArrayList<Character> l = new ArrayList<>();
			for (int i = 0; i < 80; i++) {
				l.add(' ');
			}
			for (int i = countY; i < 25; i++) {
				field.add(l);
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static void execute(String commandName, Character command) {
		if (commandName.equals("End")) {
			end = true;
			return;
		}
		if (commandName.equals("Direction")) {
			changeDirection(command);
			return;
		}
		if (commandName.equals("SymbolMode")) {
			pushSymbols();
			return;
		}
		if (commandName.equals("Empty")) {
			return;
		}
		Class<?> cl = factory.createCommand(commandName);
		Object o = factory.createInstance(cl);
		Method[] a = factory.createMethods(cl);
		for (Method m : a) {
			try {
				if (m.getName().equals("execute")) {
					m.invoke(o, stack, command, direction, field);
				}
			} catch (IllegalAccessException | IllegalArgumentException
					| InvocationTargetException e) {
				e.printStackTrace();
			}
		}
	}
}
