package ru.nsu.kolochkin.Befunge;

import java.lang.reflect.Method;
import java.util.HashMap;

public class CommandFactory {
	private static HashMap<String, Boolean> cacheMap = new HashMap<>();

	private static HashMap<String, Class<?>> classMap = new HashMap<>();

	CommandFactory() {
		cacheMap.put("ChangerVertexes", false);
		cacheMap.put("Comparison", false);
		cacheMap.put("CopierVertex", false);
		cacheMap.put("Deleter", false);
		cacheMap.put("Division", false);
		cacheMap.put("Invert", false);
		cacheMap.put("Minus", false);
		cacheMap.put("Mod", false);
		cacheMap.put("Multiplication", false);
		cacheMap.put("NumberPrint", false);
		cacheMap.put("Plus", false);
		cacheMap.put("SymbolPrint", false);
		cacheMap.put("SymbolRequest", false);
		cacheMap.put("Constant", false);
		cacheMap.put("Direction", false);
		cacheMap.put("Put", false);
		cacheMap.put("Get", false);
	}

	public static Class<?> createCommand(String commandName) {
		Class<?> cl = null;
		if (!cacheMap.get(commandName)) {
			try {
				cl = Class.forName("ru.nsu.kolochkin.Befunge.commands." + commandName);
				cacheMap.put(commandName, true);
			} catch (ClassNotFoundException e) {
				return null;
			}
			classMap.put(commandName, cl);
			return cl;
		}
		else {
			return classMap.get(commandName);
		}
	}

	public static Object createInstance(Class<?> cl) {
		Object o;
		try {
			o = cl.newInstance();
		} catch (InstantiationException | IllegalAccessException e) {
			throw new RuntimeException();
		}
		return o;
	}

	public static Method[] createMethods(Class<?> cl) {
		return cl.getDeclaredMethods();
	}
}
