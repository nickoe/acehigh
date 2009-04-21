%
% Document preamble for assignments and report
% Version 1.0
%
% Copyright (C) 2009  Kristian Kjærgaard
%
% This program is free software: you can redistribute it and/or modify
% it under the terms of the GNU General Public License as published by
% the Free Software Foundation, either version 3 of the License, or
% (at your option) any later version.
%
% This program is distributed in the hope that it will be useful, but
% WITHOUT ANY WARRANTY; without even the implied warranty of
% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
% General Public License for more details.
%
% You should have received a copy of the GNU General Public License
% along with this program.  If not, see
% <http://www.gnu.org/licenses/>.



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

\newcommand{\@isdraft}{true}


% Ensidet memoir-opsætning
\DeclareOption{final}{\renewcommand{\@isdraft}{false}}
\ProcessOptions\relax

% Klassen memoir indlæses og konfigureres

\LoadClass[11pt,a4paper,twoside]{memoir}



% Andre pakker indlæses og konfigureres

\RequirePackage{amsmath,amssymb}
\RequirePackage[danish]{babel}
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
\RequirePackage[scaled]{luximono}
%\RequirePackage[inputencoding=utf8/latin1]{listingsutf8}
\RequirePackage[adobe-utopia]{mathdesign}
%\RequirePackage{mathcomp} % bugger med mathdesign
\RequirePackage[version=3]{mhchem}
\RequirePackage{placeins}
\RequirePackage{sistyle}
  \SIdecimalsign{,}
  \SIthousandsep{.}
\RequirePackage{subfig}
\RequirePackage{textcomp}
\RequirePackage{tikz}
\RequirePackage{ulem}
\RequirePackage{url}
\RequirePackage[danish]{varioref}
\RequirePackage{xcolor}

\ifthenelse{\boolean{\@isdraft}}{
  \RequirePackage[draft,danish]{fixme}
}{}

% hyperref og fixes
\RequirePackage[colorlinks,plainpages=false,breaklinks,bookmarks]{hyperref}
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


% farver på links?
%\hypersetup{
%  citecolor=black,
%  filecolor=black,
%  linkcolor=black,
%  urlcolor=black
%}



\pagestyle{Ruled}
\addto\captionsdanish{
  \renewcommand{\chaptername}{Afsnit}
}

\captionnamefont{\small \sffamily \bfseries}
\captiontitlefont{\small}

\setlrmarginsandblock{2,8cm}{4,8cm}{*}
\setmarginnotes{0,4cm}{3,4cm}{0,4cm}

% setup for the side caption environment
\setsidecaps{0,4cm}{3,0cm}
\sidecapmargin{outer}

\newcommand{\mnote}[1]{\marginpar{\small #1}}
\newcommand{\snote}[1]{\sidebar{\small #1}}

\checkandfixthelayout


\renewcommand{\lstlistingname}{Kodeeksempel}

\definecolor{lstbg}{RGB}{204,247,221}
\lstset{
  language=C,
  numbers=left,
  numberstyle=\tiny,
  inputencoding=latin1,
  backgroundcolor=\color{lstbg},
  framerule=0pt,
  frame=single,
  framesep=5pt,
  basicstyle=\footnotesize \ttfamily
}


% Konfiguration af almindelige klasser

\let\times\cdot
\let\epsilon\varepsilon

\newcommand{\fnote}[1]{\footnote{#1}}
\newcommand{\degree}{\ensuremath{^\circ}}
