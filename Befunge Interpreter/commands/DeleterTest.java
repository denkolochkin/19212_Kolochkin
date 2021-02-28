package ru.nsu.kolochkin.Befunge.commands;

import org.junit.Test;

import java.util.Stack;

import static org.junit.Assert.*;

public class DeleterTest {

	@Test
	public void execute() {
		Deleter d = new Deleter();
		Stack<Character> stack = new Stack<>();
		stack.push('1');
		stack.push('3');
		d.execute(stack, null, null, null);
		assertNotEquals('3', (char) stack.peek());
		assertEquals('1', (char) stack.peek());
	}
}