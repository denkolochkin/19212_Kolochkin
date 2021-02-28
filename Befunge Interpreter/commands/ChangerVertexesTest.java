package ru.nsu.kolochkin.Befunge.commands;

import org.junit.Test;

import java.util.Stack;

import static org.junit.Assert.*;

public class ChangerVertexesTest {

	@Test
	public void execute() {
		ChangerVertexes c = new ChangerVertexes();
		Stack<Character> stack = new Stack<>();
		stack.push('1');
		stack.push('2');
		c.execute(stack, null, null, null);
		assertEquals('1', (char) stack.peek());
		stack.pop();
		assertEquals('2', (char) stack.peek());
	}
}