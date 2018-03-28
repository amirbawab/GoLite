#include <golite/ts_helper.h>
#include <golite/utils.h>
#include <golite/program.h>

std::string golite::TSHelper::clone_func_name_ = "clone";

bool golite::TSHelper::isObject(TypeComponent *type_component) {
    return type_component->resolvesToStruct()
           || type_component->resolvesToArray()
           || type_component->resolvesToSlice();
}

std::string golite::TSHelper::cloneObject(TypeComponent *type_component) {
    std::stringstream ss;
    if(isObject(type_component)) {
        ss << "." << getCloneCall();
    }
    return ss.str();
}

std::string golite::TSHelper::codePrint(int indent) {
    std::stringstream ss;
    ss << golite::Utils::blockComment({"Print function", "Built-in function"}, indent) << std::endl
       << golite::Utils::indent(indent) << "function golite_print(...args : any[]) : void {" << std::endl
       << golite::Utils::indent(indent+1) << "var buffer : string = \"\";" << std::endl
       << golite::Utils::indent(indent+1) << "for( var i : number = 0; i < args.length; i++) {" << std::endl
       << golite::Utils::indent(indent+2) << "buffer += args[i];" << std::endl
       << golite::Utils::indent(indent+1) << "}" << std::endl
       << golite::Utils::indent(indent+1) << "process.stdout.write(buffer);" << std::endl
       << golite::Utils::indent(indent) << "};" << std::endl
       << std::endl;
    return ss.str();
}

std::string golite::TSHelper::codePrintln(int indent) {
    std::stringstream ss;
    ss << golite::Utils::blockComment({"Print line function", "Built-in function"}, indent) << std::endl
       << golite::Utils::indent(indent) << "function golite_println(...args : any[]) : void {" << std::endl
       << golite::Utils::indent(indent+1) << "var buffer : string = \"\";" << std::endl
       << golite::Utils::indent(indent+1) << "for( var i : number = 0; i < args.length; i++) {" << std::endl
       << golite::Utils::indent(indent+2) << "if(i != 0) buffer += ' ';" << std::endl
       << golite::Utils::indent(indent+2) << "buffer += args[i];" << std::endl
       << golite::Utils::indent(indent+1) << "}" << std::endl
       << golite::Utils::indent(indent+1) << "process.stdout.write(buffer + '\\n');" << std::endl
       << golite::Utils::indent(indent) << "};" << std::endl
       << std::endl;
    return ss.str();
}

std::string golite::TSHelper::codeConstants(int indent) {
    std::stringstream ss;
    ss << golite::Utils::blockComment({"True and False constants", "Built-in variables"}, indent) << std::endl
       << golite::Utils::indent(indent)  << "var "
       << golite::Program::TRUE_VAR->getIdentifiers().back()->toTypeScript(indent) << " : "
       << golite::Program::TRUE_VAR->getTypeComponent()->toTypeScript(0) << " = true;" << std::endl
       << golite::Utils::indent(indent)  << "var "
       << golite::Program::FALSE_VAR->getIdentifiers().back()->toTypeScript(indent) << " : "
       << golite::Program::TRUE_VAR->getTypeComponent()->toTypeScript(0) << " = false;" << std::endl
       << std::endl;
    return ss.str();
}

std::string golite::TSHelper::codeArrayInterface(int indent) {
    std::stringstream ss;
    ss << golite::Utils::blockComment({"Array interface", "Built-in interface"}, indent) << std::endl
       << golite::Utils::indent(indent) << "interface Array<T> {" << std::endl
       << golite::Utils::indent(indent+1) << "check : (index : number) => Array<T>;" << std::endl
       << golite::Utils::indent(indent+1) << clone_func_name_ << " : () => Array<T>;" << std::endl
       << golite::Utils::indent(indent+1) << "init : (val : T) => Array<T>;" << std::endl
       << golite::Utils::indent(indent) << "}" << std::endl
       << golite::Utils::indent(indent) << "Array.prototype.check = function(index : number) {" << std::endl
       << golite::Utils::indent(indent+1) << "if(index < 0 || index >= this.length) {" << std::endl
       << golite::Utils::indent(indent+2) << "process.stderr.write('Error: Index out of bound' + '\\n');" << std::endl
       << golite::Utils::indent(indent+2) << "process.exit(1);" << std::endl
       << golite::Utils::indent(indent+1) << "}" << std::endl
       << golite::Utils::indent(indent+1) << "return this;" << std::endl
       << golite::Utils::indent(indent) << "}" << std::endl
       << golite::Utils::indent(indent) << "Array.prototype." << clone_func_name_ << " = function() {" << std::endl
       << golite::Utils::indent(indent+1) << "var array = [];" << std::endl
       << golite::Utils::indent(indent+1) << "for(var i : number = 0; i < this.length; i++) {" << std::endl
       << golite::Utils::indent(indent+2) << "if(this[i] instanceof Object) {" << std::endl
       << golite::Utils::indent(indent+3) << "array[i] = this[i]." << getCloneCall() <<  ";" << std::endl
       << golite::Utils::indent(indent+2) << "} else {" << std::endl
       << golite::Utils::indent(indent+3) << "array[i] = this[i];" << std::endl
       << golite::Utils::indent(indent+2) << "}" << std::endl
       << golite::Utils::indent(indent+1) << "}" << std::endl
       << golite::Utils::indent(indent+1) << "return array;" << std::endl
       << golite::Utils::indent(indent) << "}" << std::endl
       << golite::Utils::indent(indent) << "Array.prototype.init = function (val: any) {" << std::endl
       << golite::Utils::indent(indent+1) << "for (var i: number = 0; i < this.length; i++) {" << std::endl
       << golite::Utils::indent(indent+2) << "if (val instanceof Object) {" << std::endl
       << golite::Utils::indent(indent+3) << " this[i] = val." << getCloneCall() << ";" << std::endl
       << golite::Utils::indent(indent+2) << "} else {" << std::endl
       << golite::Utils::indent(indent+3) << "this[i] = val;" << std::endl
       << golite::Utils::indent(indent+2) << "}" << std::endl
       << golite::Utils::indent(indent+1) << "}" << std::endl
       << golite::Utils::indent(indent+1) << "return this;" << std::endl
       << golite::Utils::indent(indent) << "}" << std::endl
       << std::endl;
    return ss.str();
}

std::string golite::TSHelper::codeSlice(int indent) {
    std::stringstream ss;
    ss << golite::Utils::blockComment({"Slice class", "Built-in class"}, indent) << std::endl
       << golite::Utils::indent(indent) << "class Slice<T> {" << std::endl
       << golite::Utils::indent(indent+1) << "array : Array<T> = new Array<T>(0);" << std::endl
       << golite::Utils::indent(indent+1) << "append = (val : T) : Slice<T> => {" << std::endl
       << golite::Utils::indent(indent+2) << "var slice : Slice<T> = this." << getCloneCall() << ";" << std::endl
       << golite::Utils::indent(indent+2) << "slice.array.push(val);" << std::endl
       << golite::Utils::indent(indent+2) << "return slice;" << std::endl
       << golite::Utils::indent(indent+1) << "}" << std::endl
       << golite::Utils::indent(indent+1) << "check = (index : number) : Array<T> => {" << std::endl
       << golite::Utils::indent(indent+2) << "this.array.check(index);" << std::endl
       << golite::Utils::indent(indent+2) << "return this.array;" << std::endl
       << golite::Utils::indent(indent+1) << "}" << std::endl
       << golite::Utils::indent(indent+1) << clone_func_name_ << " = (): Slice<T> => {" << std::endl
       << golite::Utils::indent(indent+2) << "var slice : Slice<T> = new Slice<T>();" << std::endl
       << golite::Utils::indent(indent+2) << "slice.array = this.array." << getCloneCall() << ";" << std::endl
       << golite::Utils::indent(indent+2) << "return slice;" << std::endl
       << golite::Utils::indent(indent+1) << "}" << std::endl
       << golite::Utils::indent(indent) << "}" << std::endl
       << std::endl;
    return ss.str();
}

std::string golite::TSHelper::codeFloat(int indent) {
    std::stringstream ss;
    ss << golite::Utils::blockComment({"Format float values", "Built-in function"}, indent) << std::endl
       << golite::Utils::indent(indent) << "function golite_float(float: number): string {" << std::endl
       << golite::Utils::indent(indent+1) << "var sign : string = \"\";" << std::endl
       << golite::Utils::indent(indent+1) << "var eFloat : string = float.toExponential(6);" << std::endl
       << golite::Utils::indent(indent+1) << "if (float >= 0) sign = \"+\";" << std::endl
       << golite::Utils::indent(indent+1) << "var eIndex : number = eFloat.indexOf(\"e\");" << std::endl
       << golite::Utils::indent(indent+1) << "var eFloatVal: string = eFloat.slice(0, eIndex);" << std::endl
       << golite::Utils::indent(indent+1) << "var eSign = eFloat.slice(eIndex, eIndex+2);" << std::endl
       << golite::Utils::indent(indent+1) << "var eVal = eFloat.slice(eIndex + 2);" << std::endl
       << golite::Utils::indent(indent+1) << "if (eVal.length == 1) {" << std::endl
       << golite::Utils::indent(indent+2) << "eVal = \"00\" + eVal;" << std::endl
       << golite::Utils::indent(indent+1) << "} else if (eVal.length == 2) {" << std::endl
       << golite::Utils::indent(indent+2) << "eVal = \"0\" + eVal;" << std::endl
       << golite::Utils::indent(indent+1) << "}" << std::endl
       << golite::Utils::indent(indent+1) << "return sign + eFloatVal + eSign + eVal;" << std::endl
       << golite::Utils::indent(indent) << "}" << std::endl
       << std::endl;
    return ss.str();
}

std::string golite::TSHelper::getCloneCall() {
    std::stringstream ss;
    ss << clone_func_name_ << "()";
    return ss.str();
}