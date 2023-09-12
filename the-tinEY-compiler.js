/*
 * ============================================================================
                                        ___  __  __
                                       / _ \/ / / /
                                      /  __/ /_/ /
                                      \___/\__, /
                                          /____/
                           * Building a better working world *
 * ============================================================================
    *                                 ⌒(❀>◞౪◟<❀)⌒
    *                        Welcome to The TinEY Compiler!!!
 * ============================================================================

*/

/*

Yoo hoo! Together we will build a Python compiler using JavaScript. 

Feel free to attempt one or some or all of the sections below (in any order). 

When you're happy with your contribution, raise a PR! On the next call, we will merge the PRs together to form an end-to-end Python compiler!

Some tips before you start:
 - Keep it simple. We only need to compile the code in the example (see "THE CODE" section below). Anything beyond this is extra :) 
 - When you get stuck, look at this: https://aosabook.org/en/500L/a-python-interpreter-written-in-python.html  <---The skeleton below is based on this article
 - The skeleton below is very loose; it's possible we might need some extra functions. 
 - Remember chatGPT is your friend 
 - Good luck!
*/


/**
 * ============================================================================
 *                                   (ʘ‿ʘ)
 *                                  THE CODE!
 * ============================================================================
 * 
 * This is the Python code we want to compile: 
 * 
 * 
 * >>> def s():
 * ...     a = 1
 * ...     b = 2
 * ...     print(a + b)
 * 
 */


/**
 * ============================================================================
 *                                   (/^▽^)/
 *                                THE TOKENIZER!
 * ============================================================================
 */

//Step One: break the code into tokens. 

function tokenize(input){
    //Break the code down into tokens
    // a.k.a. Break the "sentence" into "words"
}


/**
 * ============================================================================
 *                                   (งಠ_ಠ)ง
 *                                 THE PARSER!
 * ============================================================================
 */


//Step Two: Building the Intermediate Representation 

//NOTE: It seems most python compilers do not use a "tree" structure for their Intermediate Representation. Instead, they use an Object or (more commonly) a table-like structure. 

//So after parsing our tokens, our semi-compiled code should look something like this: 

/* 
 
what_to_execute = {
        "instructions": [("LOAD_VALUE", 0),
                         ("STORE_NAME", 0),
                         ("LOAD_VALUE", 1),
                         ("STORE_NAME", 1),
                         ("LOAD_NAME", 0),
                         ("LOAD_NAME", 1),
                         ("ADD_TWO_VALUES", None),
                         ("PRINT_ANSWER", None)],
        "numbers": [1, 2],
        "names":   ["a", "b"] }

*/ 

// Or alternatively, something like this: 

/* 
LOAD_CONST 1
STORE_FAST a
LOAD_CONST 2
STORE_FAST b
LOAD_GLOBAL print
LOAD_FAST a
LOAD_FAST b
BINARY_ADD
CALL_FUNCTION 1
POP_TOP
LOAD_CONST None
RETURN_VALUE

*/

function parse(tokens){
    //Syntax errors would happen here too
    //a.k.a Grammar check 
}


/**
 * ============================================================================
 *                                   (づ￣ ³￣)づ
 *                                THE CODE GENERATOR!
 * ============================================================================
 */

//Once we have our Intermediate Representation, we can then convert it to binary code

//Following the above example, our end result should be the bytes below (I think): 

/*
b'd\x01\x00}\x00\x00d\x02\x00}\x01\x00|\x00\x00|\x01\x00\x17\x83\x01\x00\x01d\x00\x00S'
*/

function generateCode(parsedInput){
    //Super impressed if someone completes this part :) 
}


//The complete compiler: 
function compile(pythonCode){
    const tokens = tokenize(pythonCode)
    const parsedCode = parse(tokens)
    const bytes = generateCode(parsedCode)

    return bytes 
}
