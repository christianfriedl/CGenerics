#!/usr/bin/perl
use POSIX qw(strftime);
$date = strftime "%Y-%m-%d\n", localtime;

$#ARGV==1 or die "Usage: makeman.pl inputfile outputfile";
$infilename = $ARGV[0];
$infilename =~ /^(.*\/)?(\w+)(\.\w+)$/;
$srcname = $2;
$fullsourcename = $2.$3;
open FILE, "<$infilename" or die "unable to read $infilename";
$outfilepath = $ARGV[1];

while (<FILE>) {
    $do_makeman = 1;
    if (/\bNOMAKEMAN\b/) {
        $do_makeman = 1;
    }
    if (/\nMAKEMAN\b/) {
        $do_makeman = 0;
    }
    if ($do_makeman) {
        if (/^(\w+[()\w*])\s+(\w+)\s*\((.*)\)\s*;\s*$/) {
            # normal functions
            $returntype = $1;
            $name = $2;
            $args = $3;
            $code = ".Ft $returntype\n"
                    .".Fn $name ";
            foreach (split /\s*,\s*/, $args) {
                $code .= "\"$_\" ";
            }
            write_manpage($code, 'Function', "$name.3");
        } elsif (/#define\s+(\w+)\s*(\(([\w,.\s]+)\))?\s+/) {
            # funcmacros
            $name = $1;
            $args = $3;
            $code = ".Fn $name ";
            foreach (split /\s*,\s*/, $args) {
                $code .= "\"$_\" ";
            }
            write_manpage($code, 'Function Macro', "$name.3");
        } elsif (/#define\s+(\w+)\s+/) {
            # constmacros
            $name = $1;
            $code = ".Fn $name ";
            write_manpage($code, 'Constant Macro', "$name.3");
        }
    }
} 

sub write_manpage {
    my ($code, $type, $outfilename) = @_;
    open OUTFILE, ">$outfilepath/$outfilename" or die "unable to write $outfilepath/$outfilename";

    select OUTFILE;

    print ".Dd $date\n";
    print ".Dt ".(uc $srcname)." 3\n";
    print ".Os\n";
    print ".Sh NAME\n";
    print ".Nm ".$srcname."\n";
    print ".Sh LIBRARY\n";
    print ".Nm cgenerics\n";
    print ".Sh SYNOPSIS\n";
    print ".In cgenerics/$fullsourcename\n";
    print ".SS \"$type\"\n";
    print "$code\n";
}
