package ru.nsu.kolochkin.Befunge.commands;

import org.junit.Test;

import java.util.Stack;

import static org.junit.Assert.*;

public class MultiplicationTest {

	@Test
	public void execute() {
		//not works
		Multiplication m = new Multiplication();
		Stack<Character> stack = new Stack<>();
		stack.push('3');
		stack.push('2');
		m.execute(stack, null, null,null);
		assertEquals('6', stack.peek() - '0');
	}
}