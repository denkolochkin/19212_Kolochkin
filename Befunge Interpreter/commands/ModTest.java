package ru.nsu.kolochkin.Befunge.commands;

import org.junit.Test;

import java.util.Stack;

import static org.junit.Assert.*;

public class ModTest {

	@Test
	public void execute() {
		Mod m = new Mod();
		Stack<Character> stack = new Stack<>();
		stack.push('7');
		stack.push('5');
		m.execute(stack, null, null,null);
		assertEquals(2, (int) stack.peek());
	}
}