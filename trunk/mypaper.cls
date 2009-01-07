% Dokumentpreamble til afleveringer i gymnasiet
% Copyright (C) 2009  Kristian Kjærgaard <kkjaergaard@gmail.com>
%
% TODO: lav titlingpage-environment om så den centrerer teksten på
% siden og ikke på tekstområdet, gør noget ved figure- og
% table-environments - de er grimme i fysikafleveringerne\dots de er
% uoverskuelige når der er mange af dem, giv dem evt. en
% baggrundsfarve, lav siderne smallere/brug mere af siden (evt. til
% captions, tabeller m.m.)
%
% Implementer farveunderstøttelse


\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{mypaper}[2008/12/10 Afleveringsklasse]

\RequirePackage{ifthen}


% Parametrene assignment, report og essay kan ikke gives
% samtidig. Parameteren assignment er standard.

\newcommand{\@isreport}{false} % det er en assignment
\newcommand{\@isdraft}{true}
\newcommand{\@isessay}{false}
\newcommand{\@withmnote}{false}


% Ensidet memoir-opsætning
\DeclareOption{essay}{
  \renewcommand{\@isreport}{false}
  \renewcommand{\@isessay}{true}
}
\DeclareOption{report}{
  \renewcommand{\@isreport}{true}
  \renewcommand{\@isessay}{false}
}
\DeclareOption{final}{\renewcommand{\@isdraft}{false}}
\DeclareOption{mnote}{\renewcommand{\@withmnote}{true}}
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
  \renewcommand{\danishhyphenmins}{22} % bedre orddeling
\RequirePackage{bm}
\RequirePackage{capt-of}
\RequirePackage[danish=quotes]{csquotes}
  \selectlanguage{danish}
%\RequirePackage{datetime}
\RequirePackage{enumerate}
\RequirePackage{fix-cm}
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
\RequirePackage{tikz}
\RequirePackage{ulem}
\RequirePackage{url}
\RequirePackage[english,danish]{varioref}
\RequirePackage{xcolor}

\ifthenelse{\boolean{\@isdraft}}{
  \RequirePackage[draft,danish]{fixme}
}{}

\ifpdf
  \RequirePackage{pdfpages}
\fi

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

% showkeys og fix med hyperref
\ifthenelse{\boolean{\@isdraft}}{
  \RequirePackage[notref,notcite]{showkeys}
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
\hypersetup{
  citecolor=black,
  filecolor=black,
  linkcolor=black,
  urlcolor=black
}



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

\ifthenelse{\boolean{\@withmnote}}{
  \setlrmarginsandblock{2,8cm}{4,8cm}{*}
  \setmarginnotes{0,4cm}{3,4cm}{0,4cm}
  \checkandfixthelayout

  \newcommand{\mnote}[1]{\marginpar{\small #1}}

  \ifthenelse{\boolean{\@isreport}}{}{
    % Lav sidehovedet om, så det er lige langt fra kanten i begge
    % sider af papiret. Lav \maketitle-makroen om, så den er centreret
    % midt på papiret.
  }
}{}


% Konfiguration af almindelige klasser

\let\times\cdot
\let\epsilon\varepsilon

\newcommand{\fnote}[1]{\footnote{#1}}

% makroen er kun brugbar hvis man ikke skelner mellem \chapter
% og \section
\newcommand{\nosecnum}{\setcounter{secnumdepth}{-1}}


\newcommand{\facit}[1]{\uuline{#1}}
\newcommand{\SIfacit}[2]{\uuline{\SI{#1}{#2}}}
\newcommand{\degree}{\ensuremath{^\circ}}
