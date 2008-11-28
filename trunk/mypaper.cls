% Dokumentpreamble til afleveringer i gymnasiet
% Copyright (C) 2008  Kristian Kjærgaard <kkjaergaard@gmail.com>
%
% TODO: lav titlingpage-environment om så den centrerer teksten på
% siden og ikke på tekstområdet, gør noget ved figure- og
% table-environments - de er grimme i fysikafleveringerne\dots de er
% uoverskuelige når der er mange af dem, giv dem evt. en
% baggrundsfarve, lav siderne smallere/brug mere af siden (evt. til
% captions, tabeller m.m.)


\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{mypaper}[2008/09/24 Afleveringsklasse]

\RequirePackage{ifthen}

% Parametrene assignment, report og essay kan ikke gives
% samtidig. Parameteren assignment er standard.

\newcommand{\@isreport}{false} % det er en assignment
\newcommand{\@iscolor}{false} % vi udskriver sort/hvid
\newcommand{\@isdraft}{true}
\newcommand{\@isessay}{false}
\newcommand{\@showkeys}{false}


% Ensidet memoir-opsætning
\DeclareOption{report}{\renewcommand{\@isreport}{true}}
\DeclareOption{color}{\renewcommand{\@iscolor}{true}}
\DeclareOption{final}{\renewcommand{\@isdraft}{false}}
\DeclareOption{essay}{\renewcommand{\@isessay}{true}}
\DeclareOption{showkeys}{\renewcommand{\@showkeys}{true}}
\ProcessOptions\relax

\ifthenelse{\boolean{\@isreport}}{
  \PassOptionsToClass{twoside}{memoir}
}{
  \PassOptionsToClass{oneside,article}{memoir}
}

\ifthenelse{\boolean{\@isessay}}{
  \PassOptionsToClass{twocolumn}{memoir}
}{}


% Klassen memoir indlæses og konfigureres

\LoadClass[11pt,a4paper]{memoir}



% Andre pakker indlæses og konfigureres

\RequirePackage{amsmath,amssymb}
\RequirePackage[english,danish]{babel}
\RequirePackage{bm}
\RequirePackage[danish=quotes]{csquotes}
  \selectlanguage{danish}
\RequirePackage{datetime}
\RequirePackage{enumerate}
\RequirePackage{fixltx2e}
\RequirePackage[T1]{fontenc}
\RequirePackage{graphicx}
\RequirePackage{icomma}
\RequirePackage[utf8]{inputenc}
\RequirePackage{lipsum}
\RequirePackage{listings}
\RequirePackage[utopia]{mathdesign}
%\RequirePackage{mathcomp} % bugger med mathdesign
\RequirePackage[version=3]{mhchem}
\RequirePackage{placeins}
\RequirePackage{sistyle}
  \SIdecimalsign{,}
  \SIthousandsep{.}
\RequirePackage{textcomp}
\RequirePackage{ulem}
\RequirePackage{url}
\RequirePackage[english,danish]{varioref}
\RequirePackage{xcolor}




% Almindelige klasser på betingelser

\ifthenelse{\boolean{\@isdraft}}{
  \RequirePackage[draft]{fixme}
}{}

\ifpdf
  \RequirePackage{pdfpages}
\fi


% Generel opsætning til assignment-stilen
\ifthenelse{\boolean{\@isreport}}{
  % report
  \addto\captionsdanish{
    \renewcommand{\chaptername}{Afsnit}
  }
  \pagestyle{Ruled}
}{
  % assignment
  \makepagestyle{front}
  \aliaspagestyle{title}{front}
  \aliaspagestyle{plain}{front}
  %\aliaspagestyle{empty}{front}

  \makepagestyle{pst}
  \makeoddhead{pst}{\theauthor}{\thetitle}{\thedate}
  \makeoddfoot{pst}{}{\thepage}{}
  \makeheadrule{pst}{\textwidth}{\normalrulethickness}
  \pagestyle{pst}
  \setcounter{secnumdepth}{1} % todo: tjek om det burde være anderledes
  \RequirePackage{tocloft}
}


\captionnamefont{\small \sffamily \bfseries}
\captiontitlefont{\small}
% \hangcaption % skal den aktiveres igen? nej?
\captionwidth{0.85\textwidth}
\changecaptionwidth

% Lav en tekstboks nederst/øverst på første side hvor der står hvornår
% filen er gerereret, hvilken sidestil der er brugt, programversion,
% forfatter m.m.


% hyperref og fixes
\RequirePackage[colorlinks,plainpages=false,breaklinks]{hyperref}
\RequirePackage{memhfixc} % fix med memoir
\RequirePackage{nameref} % fix med what?
\ifpdf % fix med latex, dvips eller...?
\else
  \RequirePackage{breakurl}
\fi
% hyperref + varioref fix
\def\Hy@varioref@undefined{{??}{??}{}{}{}}
\@ifpackageloaded{varioref}{%
\def\vref@pagenum#1#2{%
  \@ifundefined{r@#2}{%
    \expandafter\let\csname r@#2\endcsname\Hy@varioref@undefined
  }{}%
  \edef#1{\getpagerefnumber{#2}}%
}%
}{}


% ting der nødvendigvis indlæses /efter/ hyperref


% showkeys og fix med hyperref
\ifthenelse{\boolean{\@showkeys}}{
  \RequirePackage[notref,notcite,color]{showkeys}
  \let\HyRef@ShowKeysRef\@gobble
  \def\HyRef@ShowKeysInit{
    \begingroup\expandafter\expandafter\expandafter\endgroup
    \expandafter\ifx\csname SK@@label\endcsname\relax
    \else
      \ifx\SK@ref\@empty
      \else
        \def\HyRef@ShowKeysRef{
          \SK@\SK@@ref
        }
      \fi
    \fi
  }
  \@ifpackageloaded{showkeys}{
    \HyRef@ShowKeysInit
  }{
    \AtBeginDocument{
      \@ifpackageloaded{showkeys}{
        \HyRef@ShowKeysInit
      }{}
    }
  }
}

% farver på links?
\ifthenelse{\boolean{\@iscolor}}{}{
  \hypersetup{
    citecolor=black,
    filecolor=black,
    linkcolor=black,
    urlcolor=black
  }
}


% Konfiguration af almindelige klasser

\let\times\cdot
\let\epsilon\varepsilon

% makroen er kun brugbar hvis man ikke skelner mellem \chapter
% og \section
\newcommand{\nosecnum}{\setcounter{secnumdepth}{-1}}


\newcommand{\facit}[1]{\uuline{#1}}
\newcommand{\SIfacit}[2]{\uuline{\SI{#1}{#2}}}
\newcommand{\degree}{\ensuremath{^\circ}}

\newcommand\vect[2]{\begin{pmatrix}#1\\#2\end{pmatrix}}

\renewcommand{\danishhyphenmins}{22} % bedre orddeling


\checkandfixthelayout