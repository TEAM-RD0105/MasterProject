%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                   0105 TEAM TCU CONTROL SOFTWARE
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%-------------------------------------------------------------------------
% DESCRIPTION
%-------------------------------------------------------------------------
%   This file sets up the paths and calls the relevant paramater files for
%   the SB CVT Control Software for RD0081 TEAM ATV SB
%------------------------------------------------------------------------- 
% Date Created: 	02/27/2025
% Created by: 		C Romo
% Last Update: 		-
% Updated by:  		- 
%------------------------------------------------------------------------- 
%-------------------------------------------------------------------------

% This script will set up the correct Matlab environment for software
% development and simulation

clc
root = fileparts(mfilename("fullpath"));

genRoot   = fullfile(root, "GeneratedFiles");
cacheRoot = fullfile(genRoot, "Cache");
codeRoot  = fullfile(genRoot, "CodeGen");

Simulink.fileGenControl("set", ...
    "CacheFolder",  cacheRoot, ...
    "CodeGenFolder", codeRoot, ...
    "createDir", true);

p = split(string(genpath(root)), pathsep);
p = p(p ~= "");

exclude = ["GeneratedFiles","slprj","_sfprj","_jitprj","tmwinternal","ert_rtw","_ert_rtw"];
p = p(~contains(p, exclude, "IgnoreCase", true));

addpath(strjoin(p, pathsep));
clc

clear root genRoot cacheRoot codeRoot p exclude

% End
