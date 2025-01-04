#pragma once

// ReSharper disable CppPolymorphicClassWithNonVirtualPublicDestructor
// ReSharper disable CppClangTidyCppcoreguidelinesAvoidConstOrRefDataMembers

struct Document;

struct IMachine
{
	virtual void print(Document& document) = 0;
	virtual void scan(Document& document) = 0;
	virtual void fax(Document& document) = 0;
};

struct MultiFunctionPrinter : IMachine
{
	void print(Document& document) override { /* OK */ }
	void scan(Document& document) override { /* OK */ }
	void fax(Document& document) override { /* OK */ }
};

struct Scanner : IMachine
{
	void print(Document& document) override { /* Wrong information to the client */ }
	void scan(Document& document) override { /* OK */ }
	void fax(Document& document) override { /* Wrong information to the client */ }
};


struct IPrinter
{
	virtual void print(Document& document) = 0;
};

struct IScanner
{
	virtual void scan(Document& document) = 0;
};

struct IFax
{
	virtual void fax(Document& document) = 0;
};


struct Printer : IPrinter
{
	void print(Document& document) override { /* OK */ } 
};

struct Machine : IPrinter, IScanner
{
	IPrinter& printer;
	IScanner& scanner;

	Machine(IPrinter& printer, IScanner& scanner) : printer(printer), scanner(scanner) {}

	void print(Document& document) override { printer.print(document); }
	void scan(Document& document) override { scanner.scan(document); }
};