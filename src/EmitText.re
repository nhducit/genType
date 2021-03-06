type nameGen = Hashtbl.t(string, int);

let name = (~nameGen, s) =>
  switch (Hashtbl.find(nameGen, s)) {
  | n =>
    Hashtbl.replace(nameGen, s, n + 1);
    s ++ string_of_int(n + 1);
  | exception Not_found =>
    Hashtbl.replace(nameGen, s, 0);
    s;
  };

let parens = xs => "(" ++ (xs |> String.concat(", ")) ++ ")";

let arg = (~nameGen, x) => "Arg" ++ x |> name(~nameGen);

let argi = (~nameGen, i) => "Arg" ++ (i |> string_of_int) |> name(~nameGen);

let array = xs => "[" ++ (xs |> String.concat(", ")) ++ "]";

let brackets = x => "{ " ++ x ++ " }";

let comment = x => "/* " ++ x ++ " */";

let funCall = (~args, name) =>
  name ++ "(" ++ (args |> String.concat(", ")) ++ ")";

let funDef = (~args, ~indent, ~mkBody, functionName) => {
  let indent1 = indent |> Indent.more;
  let (params, vals) = List.split(args(~indent=indent1));
  "function "
  ++ (functionName == "" ? "_" : functionName)
  ++ (params |> parens)
  ++ " {"
  ++ Indent.break(~indent=indent1)
  ++ (vals |> mkBody(~indent=indent1))
  ++ Indent.break(~indent)
  ++ "}";
};

let ifThenElse = (~indent, if_, then_, else_) => {
  let indent1 = indent |> Indent.more;
  if_(~indent=indent1)
  ++ Indent.break(~indent)
  ++ "? "
  ++ then_(~indent=indent1)
  ++ Indent.break(~indent)
  ++ ": "
  ++ else_(~indent=indent1);
};

let newNameGen = () => Hashtbl.create(1);

let quotes = x => "\"" ++ x ++ "\"";

let resultName = (~nameGen) => "result" |> name(~nameGen);

let switch_ = (~indent, ~cases, expr) => {
  let lastCase = (cases |> List.length) - 1;

  cases
  |> List.mapi((i, (label, code)) =>
       if (i == lastCase) {
         code;
       } else {
         expr
         ++ "==="
         ++ label
         ++ Indent.break(~indent)
         ++ "? "
         ++ code
         ++ Indent.break(~indent)
         ++ ": ";
       }
     )
  |> String.concat("");
};

let typeOfObject = x => "typeof(" ++ x ++ ")" ++ " === " ++ "\'object\'";