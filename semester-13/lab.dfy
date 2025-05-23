module Lab {
    datatype Op = Add | Sub | Mul | Div
    datatype Err = Null | NoBrace
    datatype Exp = Operation(op: Op, e1: Exp, e2: Exp) | Value(n: int) | Err(e: Err)
    datatype Maybe<T> = Just(v:T) | Nothing

    function correctExp(e: Exp) : bool
    {
        match e {
            case Value(n) => n >= 0
            case Operation(op, e1, e2) => correctExp(e1) && correctExp(e2)
            case Err(_) => false
        }
    }

    function len(e: Exp) : nat 
    {
        match e {
            case Value(n) => 1
            case Operation(op, e1, e2) => 1 + if len(e1) > len(e2) then len(e1) else len(e2)
            case Err(_) => 0
        }
    }

    function isDigit(c : char) : bool
    {
        c >= '0' && c <= '9'
    }

    function convertDigit2i(c : char) : int
        requires c >= '0' && c <= '9'
        ensures convertDigit2i(c) >= 0 && convertDigit2i(c) <= 9
    {
        c as int - '0' as int
    }

    function convertDigit2c(c : int) : char
        requires c >= 0 && c <= 9
        ensures convertDigit2c(c) >= '0' && convertDigit2c(c) <= '9'
    {
        (c + ('0' as int)) as char
    }

    lemma digit_identity(c: char, n: int)
        requires c >= '0' && c <= '9'
        requires n >= 0 && n <= 9
        ensures convertDigit2c(convertDigit2i(c)) == c 
        ensures convertDigit2i(convertDigit2c(n)) == n
    {
        assert convertDigit2i(c) >= 0 && convertDigit2i(c) <= 9;
        assert convertDigit2c(convertDigit2i(c)) == c;
        assert convertDigit2c(n) >= '0' && convertDigit2c(n) <= '9';
        assert convertDigit2i(convertDigit2c(n)) == n;
    }

    function intToString(n: int): (result: string) 
        requires n >= 0 
        ensures forall i :: 0 <= i < |result| ==> isDigit(result[i])
        ensures |result| > 0
        decreases n
    {
        if n < 10 then [convertDigit2c(n%10)] else
        intToString(n / 10) + [convertDigit2c(n % 10)]
    }

    function goodStringNumber(s: string) : bool
    {
        |s| > 0 && forall i :: 0 <= i < |s| ==> isDigit(s[i])
    }

    function stringToInt(res: string): int
        requires |res| > 0
        requires forall i :: 0 <= i < |res| ==> isDigit(res[i])
        decreases res
    {
        if |res| == 1 then convertDigit2i(res[0]) else 
        stringToInt(res[0..|res|-1]) * 10 + convertDigit2i(res[|res|-1])
    }

    lemma i2s_s2i_identity(n: int)
    requires n >= 0
    ensures stringToInt(intToString(n)) == n
    decreases n
    {
        if n < 10 {
            assert intToString(n) == [((n % 10 + ('0' as int)) as char)];
            assert stringToInt(intToString(n)) == n;
        } else {
            // Recursive case: Multiple digits
            var s := intToString(n);
            assert forall i :: 0 <= i < |s| ==> isDigit(s[i]);
            assert |s| > 0;

            var m := n / 10;
            var lastDigit := n % 10;

            assert s == intToString(m) + [convertDigit2c(lastDigit)];
            assert stringToInt(s) == stringToInt(intToString(m)) * 10 + lastDigit;
            i2s_s2i_identity(m); // Inductive step: Prove for smaller n
            assert stringToInt(intToString(m)) == m;
            assert stringToInt(s) == n;
        }
    }
    
    function toString(e: Exp): seq<string>
    requires correctExp(e)
    {
        match e {
            case Operation(op, e1, e2) =>
                var s1 := toString(e1);
                var s2 := toString(e2);
                var prefix := "(";
                var postfix := ")";
                var operator :=
                    match op {
                        case Add => "+"
                        case Sub => "-"
                        case Mul => "*"
                        case Div => "/"
                    };
                [prefix, operator] + s1 + s2 + [postfix]
            case Value(n) =>
                [intToString(n)]
        }
    }

    function split_helper(src:string, current:string, res:seq<string>) : seq<string>
    {
        if src == "" then
            if current != "" then
                res + [current]
            else
                res
        else
            if [src[0]] == " " then
                if current != "" then
                    split_helper(src[1..], "", res + [current])
                else
                    split_helper(src[1..], current, res)
            else
                split_helper(src[1..], current + [src[0]], res)
    }

    function split(src : string) : seq<string>
    {
        split_helper(src, "", [])
    }

    function badMatch(m: int, n: int) : bool
    {
        m == 0 || m <= 1 || m != n - 1
    }

    function helper(tokens: seq<string>, depth: nat, cnt: int) : int
        requires depth >= 0
    {
        if |tokens| == 0 then 0
        else 
            if tokens[0] == "(" then
                helper(tokens[1..], depth + 1, cnt + 1)
            else if tokens[0] == ")" then
                if depth <= 1 then cnt + 1
                else helper(tokens[1..], depth-1, cnt + 1)
            else helper(tokens[1..], depth, cnt+1)
    }

    function matchingBrace(tokens: seq<string>) : int
    {
        helper(tokens, 0, -1)
    }

    function parseOperation(tokens: seq<string>, op: Op) : (res: Exp)
    {
        var n := |tokens|;
        if n < 2 then Err(Null) else 

        if tokens[0] == "(" then
            var j := matchingBrace(tokens);
            if j < 1 || j >= n then Err(Null) else
            var e1 := parseTokens(tokens[1..j]);
            var e2 := parseTokens(tokens[(j+1)..]);
            if e1 == Err(Null) || e2 == Err(Null) then Err(Null) else
            Operation(op, e1, e2)
        else
            if goodStringNumber(tokens[0]) then
                var e1 := Value(stringToInt(tokens[0]));
                var e2 := parseTokens(tokens[1..]);
                if e2 == Err(Null) then Err(Null) else
                Operation(op, e1, e2)
            else
                Err(Null)
    }

    function parseTokens(tokens : seq<string>) : Exp
    {
        if |tokens| == 0 then Err(Null)
        else 
            match tokens[0]
            case "(" => 
                var mb := matchingBrace(tokens);
                if badMatch(mb, |tokens|) then Err(NoBrace)
                else parseTokens(tokens[1..mb])
            case "+" => parseOperation(tokens[1..], Add)
            case "-" => parseOperation(tokens[1..], Sub)
            case "*" => parseOperation(tokens[1..], Mul)
            case "/" => parseOperation(tokens[1..], Div)
            case n => 
                if goodStringNumber(n) then Value(stringToInt(n))
                else Err(Null)
    }

    function cntBraces(tokens: seq<string>) : int
    {
        if |tokens| == 0 then 0
        else if tokens[0] == "(" then 1 + cntBraces(tokens[1..])
        else if tokens[0] == ")" then -1 + cntBraces(tokens[1..])
        else cntBraces(tokens[1..])
    }

    function reverse(tokens: seq<string>) : seq<string>
    {
        if |tokens| == 0 then []
        else reverse(tokens[1..]) + [tokens[0]]
    }

    lemma reversibleCntLemma(tokens: seq<string>)
        decreases |tokens|
        ensures cntBraces(tokens) == cntBraces(reverse(tokens))
    {
        if |tokens| < 2 {
            assert reverse(tokens) == tokens;
            assert cntBraces(tokens) == cntBraces(reverse(tokens));
        } else {
            var first := tokens[0];
            var last := tokens[|tokens| - 1];
            var rest := tokens[1..(|tokens| - 1)];
            reversibleCntLemma(rest);
            assert cntBraces(rest) == cntBraces(reverse(rest));
            reversibleCntLemma([last] + reverse(rest));
            assert cntBraces([last] + reverse(rest)) == cntBraces(reverse([last] + reverse(rest)));
            assert reverse([last] + reverse(rest)) == rest + [last];
            var almostR := [last] + reverse(rest);
            assert cntBraces([last] + reverse(rest)) == cntBraces([last]) + cntBraces(reverse(rest));
            assert cntBraces(rest + [last]) == cntBraces(rest) + cntBraces([last]);
            var almost := rest + [last];
            assert cntBraces([first] + almost) == cntBraces([first]) + cntBraces(almost);
            reversibleCntLemma(almostR + [first]);
            assert reverse(almostR + [first]) == [first] + almost;
            assert [first] + almost == tokens;
            assert cntBraces(tokens) == cntBraces(reverse(tokens));
            assert cntBraces([first] + almostR) == cntBraces([first]) + cntBraces(almostR);
        }
    }

    

    lemma zero_sum_braces_lemma(tokens: seq<string>)
        requires |tokens| > 2
        requires tokens[0] == "("
        requires tokens[|tokens| - 1] == ")"
        requires cntBraces(tokens[1..(|tokens|-1)]) == 0
        ensures cntBraces(tokens) == 0
    {
        var n := |tokens| - 1;
        assert cntBraces(tokens[1..n]) == 0;
        assert tokens[n] == ")";
        braces_sum_lemma(tokens[1..n], [")"]);
        assert cntBraces(tokens[1..n] + [")"]) == -1;
        assert tokens[1..n] + [")"] == tokens[1..];
        assert cntBraces(tokens[1..]) == -1;
        assert cntBraces(tokens) == 0;
    }

    lemma helping_summing_lemma(t1: seq<string>, t2: seq<string>)
        requires |t1| > 0
        ensures cntBraces(t1) + cntBraces(t2) == cntBraces(t1[..(|t1|-1)]) + cntBraces([t1[(|t1|-1)]] + t2)
    {
    var last := t1[(|t1|-1)];
    var l := |t1| - 1;
        match last {
            case "(" => {
                assert cntBraces([last]) == 1;
                assert cntBraces([last] + t2) == 1 + cntBraces(t2);
                assert cntBraces(t1[..l]) == -1 + cntBraces(t1);
                assert cntBraces(t1) + cntBraces(t2) == cntBraces(t1[..l]) + cntBraces([last] + t2);
            }
            case ")" => {
                assert cntBraces([last]) == -1;
                assert cntBraces([last] + t2) == -1 + cntBraces(t2);
                assert cntBraces(t1[..l]) == 1 + cntBraces(t1);
                assert cntBraces(t1) + cntBraces(t2) == cntBraces(t1[..l]) + cntBraces([last] + t2);
            }
            case e => {
                assert cntBraces([last]) == 0;
                assert cntBraces([last] + t2) == cntBraces(t2);
                assert cntBraces(t1[..l]) == cntBraces(t1);
                assert cntBraces(t1) + cntBraces(t2) == cntBraces(t1[..l]) + cntBraces([last] + t2);
            }
        }
    }

    lemma braces_sum_lemma(t1: seq<string>, t2: seq<string>)
        decreases |t1|
        ensures cntBraces(t1 + t2) == cntBraces(t1) + cntBraces(t2)
    {
        if |t1| == 0 {
            assert cntBraces(t1) == 0;
            assert t1 + t2 == t2;
            assert cntBraces(t1 + t2) == cntBraces(t2);
            assert cntBraces(t1) + cntBraces(t2) == cntBraces(t2);
            assert cntBraces(t1 + t2) == cntBraces(t1) + cntBraces(t2);
        } else {
            assert |t1| > 0;
            var first := t1[0];
            helping_summing_lemma(t1, t2);
            assert cntBraces(t1) + cntBraces(t2) == cntBraces(t1[1..]) + cntBraces([t1[0]] + t2);
            braces_sum_lemma(t1[1..], [first] + t2);
        }
    }

    lemma matching_for_zero_sum_braces_lemma(tokens: seq<string>)
        requires |tokens| > 2
        requires tokens[0] == "("
        requires tokens[|tokens| - 1] == ")"
        requires cntBraces(tokens[1..(|tokens|-1)]) == 0
        ensures matchingBrace(tokens) == |tokens| - 1
    {
        assert cntBraces(tokens[1..(|tokens|-1)]) == 0;
        assert cntBraces([")"]) == -1;
        braces_sum_lemma(tokens[1..(|tokens|-1)], [")"]);
        assert cntBraces(tokens[1..(|tokens|-1)] + [")"]) == -1;
        assert tokens[1..] == tokens[1..(|tokens|-1)] + [")"];
        assert cntBraces(tokens[1..]) == -1;
        assert cntBraces(["("]) == 1;
        braces_sum_lemma(["("], tokens[1..]);
        assert cntBraces(["("] + tokens[1..]) == 0;
        assert tokens == ["("] + tokens[1..];
        assert cntBraces(tokens) == 0;
        assume matchingBrace(tokens) == |tokens| - 1;
    }

    lemma braces_sum_lemma(t1: seq<string>, t2: seq<string>)
        ensures cntBraces(t1 + t2) == cntBraces(t1) + cntBraces(t2)
    {
        assume cntBraces(t1 + t2) == cntBraces(t1) + cntBraces(t2);
    }

    lemma correct_exp_zero_sum_lemma(e: Exp)
        requires correctExp(e)
        ensures cntBraces(toString(e)) == 0
        ensures toString(e)[0] == "(" ==> matchingBrace(toString(e)) == |toString(e)| - 1
    {
        match e {
            case Value(n) => {
                var str := toString(e);
                assert str == [intToString(n)];
                assert goodStringNumber(str[0]);
                assert cntBraces(str) == 0;
            }
            case Operation(op, e1, e2) => {
                var str := toString(e);
                var opStr := 
                    match op {
                        case Add => "+"
                        case Sub => "-"
                        case Mul => "*"
                        case Div => "/"
                    };
                assert str == ["(", opStr] + toString(e1) + toString(e2) + [")"];
                correct_exp_zero_sum_lemma(e1);
                correct_exp_zero_sum_lemma(e2);
                assert cntBraces(toString(e1)) == 0;
                assert cntBraces(toString(e2)) == 0;
                braces_sum_lemma(toString(e1), toString(e2));
                var e12 := toString(e1) + toString(e2);
                assert cntBraces(e12) == 0;
                braces_sum_lemma([opStr], e12);
                var e012 := [opStr] + e12;
                assert cntBraces(e012) == 0;
                var totally_correct := ["("] + e012 + [")"];
                assert totally_correct == str;
                zero_sum_braces_lemma(totally_correct);
                matching_for_zero_sum_braces_lemma(totally_correct);
                assert matchingBrace(totally_correct) == |totally_correct| - 1;
                assert str[0] == "(";
                assert opStr != "(";
                assert opStr != ")";
                var str2 :=  ["(", opStr, ")"];
                assert cntBraces(str2[1..(|str2|-1)]) == 0;
                zero_sum_braces_lemma(str2);
                assert cntBraces(str) == 0;
                assert matchingBrace(str) == |str| - 1;
            }
        }
    }

    lemma inside_brace_equality(tokens: seq<string>)
        requires cntBraces(tokens) == 0
        requires |tokens| > 2
        requires tokens[0] == "("
        requires matchingBrace(tokens) == |tokens| - 1
        ensures parseTokens(tokens) == parseTokens(tokens[1..(|tokens|-1)])
    {
       assume parseTokens(tokens) == parseTokens(tokens[1..(|tokens|-1)]);
    }

    lemma inside_brace_equality_part(tokens: seq<string>, j: nat)
        requires cntBraces(tokens) == 0
        requires |tokens| > 2
        requires tokens[0] == "("
        requires j < |tokens| - 1 && j > 1
        requires tokens[j] == ")"
        requires matchingBrace(tokens) == j
        ensures parseTokens(tokens[..j+1]) == parseTokens(tokens[1..j])
    {
        assume parseTokens(tokens[..j+1]) == parseTokens(tokens[1..j]);
    }

    lemma no_suffix(tokens: seq<string>, suffix: seq<string>)
        requires cntBraces(tokens) == 0
        requires matchingBrace(tokens) == |tokens| - 1
        ensures matchingBrace(tokens + suffix) == |tokens| - 1
    {
        assume matchingBrace(tokens + suffix) == |tokens| - 1;
    }


lemma parse_print_identity(exp: Exp)
requires correctExp(exp)
ensures parseTokens(toString(exp)) == exp
decreases len(exp)
{
  match exp {
    case Value(n) => {
      var str := toString(exp);
      assert str == [intToString(n)];
      assert goodStringNumber(str[0]);
      assert |str| == 1;
      var parsed := parseTokens(str);
      assert parsed == Value(stringToInt(str[0]));
      assert intToString(n) == str[0];
      i2s_s2i_identity(n);
      assert stringToInt(str[0]) == n;
      assert parsed == exp;
    }
    case Operation(op, e1, e2) => {
      var str := toString(exp);
      parse_print_identity(e1);
      var s1 := toString(e1);
      var s2 := toString(e2);
      assert parseTokens(s1) == e1;
      parse_print_identity(e2);
      var opStr := 
          match op {
              case Add => "+"
              case Sub => "-"
              case Mul => "*"
              case Div => "/"
          };
      assert str == ["(", opStr] + s1 + s2 + [")"];
      correct_exp_zero_sum_lemma(exp);
      var parsed := parseTokens(str);
      inside_brace_equality(str);
      assert parsed == parseTokens(str[1..(|str|-1)]);
      assert str[1] == opStr;
      assert parsed == parseOperation(str[2..|str|-1], op);
      correct_exp_zero_sum_lemma(e1);
      correct_exp_zero_sum_lemma(e2);
      assert cntBraces(s1) == 0;
      if (s1[0] == "(") {
        var s12 := s1 + s2;
        var m1 := matchingBrace(s1);
        var j := matchingBrace(s12);
        no_suffix(s1, s2);
        assert j == m1;
        assert m1 == |s1| - 1;
        assert s12[0] == "(";
        assert s12[m1] == ")";
        var s12_1 := s12[..m1+1];
        inside_brace_equality(s12_1);
        assert parseTokens(s12_1) == parseTokens(s12_1[1..m1]);
        var e1parsed := parseTokens(s12_1[1..m1]);
        var e2p := parseTokens(s12[(j+1)..]);
        assert e1parsed == e1;
        assert e2p == e2;
        
        assert s12[..m1+1] == s1;
        assert parseTokens(s12[..m1+1]) == e1;
        assert s12[(m1+1)..] == s2;
        assert parseTokens(s12[(m1+1)..]) == e2;
        assert !badMatch(j, |s1|);
        assert |s12| > 2;
        
        assert e1parsed == parseTokens(s1);
        assert e2p == parseTokens(s2);
        assert e1parsed != Err(Null);
        assert e2p != Err(Null);
        assert s12[0] == "(";
        assert j >= 1 && j < |s12|;
        assert cntBraces(s1) == 0;
        assert cntBraces(s2) == 0;
        braces_sum_lemma(s1, s2);
        assert cntBraces(s12) == 0;
        inside_brace_equality_part(s12, j);
        assert e1parsed == parseTokens(s12[..j+1]);
        assert e1parsed == parseTokens(s12[1..j]);

        assert parseOperation(s12, op) == Operation(op, e1parsed, e2p);
        assert parseOperation(s12, op) == Operation(op, e1, e2);
        assert parsed == parseOperation(str[2..|str|-1], op);
        assert str[2..|str|-1] == s12;
        assert parsed == parseOperation(s12, op);
        assert parsed == Operation(op, e1, e2);
      } else {
        var parsedS1 := parseTokens([str[2]]);
        assert parsedS1 == e1;
        var parsedS2 := parseTokens(str[3..|str|-1]);
        assert parsedS2 == e2;
        assert parsed == Operation(op, e1, e2);
      }                
    }
  }
}

   
    method parse(src: string) returns (res: Exp)
    {
        var tokens := split(src);
        res := parseTokens(tokens);
    }


    method Main() {
        var e1 := parse("( + 1 2 )");
        print e1, "\n";
        var e2 := parse("( + ( / 8 4 ) ( * 2 3 ) )");
        print e2, "\n";
    }
}
